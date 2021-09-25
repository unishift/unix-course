#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#define HEADER_POS 0
#define WINDOW_POS 1

void read_lines(FILE* file, int* nb_lines, char*** lines, size_t** lines_len) {
    size_t cur_line = 0;
    size_t read_len;
    char* line = NULL;

    *lines = NULL;
    *lines_len = NULL;

    int read;
    while ((read = getline(&line, &read_len, file)) != -1) {
        *lines = realloc(*lines, (cur_line + 1) * sizeof(char*));
        *lines_len = realloc(*lines_len, (cur_line + 1) * sizeof(size_t));

        (*lines)[cur_line] = line;
        (*lines_len)[cur_line] = strlen(line);

        cur_line++;
        line = NULL;
    }

    *nb_lines = cur_line;
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
    keypad(stdscr, true);
    // Window
    WINDOW* win = newwin(LINES - WINDOW_POS, COLS, WINDOW_POS, 0);
    keypad(win, TRUE);
    scrollok (win, TRUE);

    // Get info
    int height, width;
    getmaxyx(win, height, width);

    // Read file
    int nb_lines;
    char** lines;
    size_t* lines_len;
    read_lines(f, &nb_lines, &lines, &lines_len);

    // Show header
    move(HEADER_POS, 0);
    printw("File: %s", argv[1]);
    refresh();

    char* line;
    size_t len;
    unsigned int start_row = 0;
    unsigned int start_col = 0;
    int run = 1;
    while (run) {
        // Show window
        wclear(win);
        wmove(win, WINDOW_POS, 0);
        for (int i = 0; i < height - 2 && start_row + i < nb_lines; i++) {
            size_t row = start_row + i;
            char* line_to_print = NULL;

            if (start_col < lines_len[row]) {
                line_to_print = lines[row] + start_col;
            } else {
                line_to_print = "\n";
            }
            wprintw(win, "%4d: %s", row, line_to_print);
        }
        box(win, 0, 0);
        wrefresh(win);

        // Handle keys
        int ch = getch();
        switch (ch) {
        case ' ':
        case KEY_DOWN:
            if (start_row + 1 < nb_lines) start_row++;
            break;
        case KEY_UP:
            if (start_row > 0) start_row--;
            break;
        case KEY_LEFT:
            if (start_col > 0) start_col--;
            break;
        case KEY_RIGHT:
            start_col++;
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
