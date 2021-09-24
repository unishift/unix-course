#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#define HEADER_POS 0
#define WINDOW_POS 1

char** read_lines(FILE* file, int* nb_lines) {
    size_t cur_line = 0;
    size_t read_len;
    char* line = NULL;
    char** lines = NULL;

    int read;
    while ((read = getline(&line, &read_len, file)) != -1) {
        lines = realloc(lines, (cur_line + 1) * sizeof(char*));
        lines[cur_line] = line;
        cur_line++;
        line = NULL;
    }

    *nb_lines = cur_line;

    return lines;
}

void free_lines(char** lines, int nb_lines) {
    for (int i = 0; i < nb_lines; i++) {
        free(lines[i]);
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Invalid number of arguments\nUsage: %s /path/to/file\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Setup
    const char* file_path = argv[1];
    FILE* f = fopen(file_path, "r");
    if (f == NULL) {
        printf("Unable to open file: %s\n", file_path);
        return EXIT_FAILURE;
    }
    initscr();
    noecho();
    curs_set(0);
    cbreak();
    // Window
    WINDOW* win = newwin(LINES - WINDOW_POS, COLS, WINDOW_POS, 0);
    keypad(win, TRUE);
    scrollok (win, TRUE);

    // Get info
    int height, width;
    getmaxyx(win, height, width);

    // Read file
    int nb_lines;
    char** lines = read_lines(f, &nb_lines);

    // Show header
    move(HEADER_POS, 0);
    printw("File: %s", argv[1]);
    refresh();

    char* line;
    size_t len;
    unsigned int start_row = 0;
    int run = 1;
    while (run) {
        // Show window
        wclear(win);
        wmove(win, WINDOW_POS, 0);
        for (int i = 0; i < height - 2 && start_row + i < nb_lines; i++) {
            wprintw(win, "%4d: %s", start_row + i, lines[start_row + i]);
        }
        box(win, 0, 0);
        wrefresh(win);

        // Handle keys
        int ch = getch();
        switch (ch) {
        case ' ':
            if (start_row + 1 < nb_lines) start_row++;
            break;
        case 27:  // ESC
            run = 0;
            break;
        default:
            break;
        }
    }

    free_lines(lines, nb_lines);
    free(lines);
    endwin();
    fclose(f);
    return EXIT_SUCCESS;
}
