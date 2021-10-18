#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

typedef struct {
    long start, stop, step;
    long curr;
} range;

void print_help() {
    const char help_message[] = 
        "This is a generator program to print integer ranges\n"
        "Usage:\n"
        "/path/to/program stop\n"
        "/path/to/program start stop\n"
        "/path/to/program start stop step\n\n"
        "Where start, stop and step are integer numbers\n";
    printf(help_message);
}

long get_number(char str[]) {
    char *end_ptr;
    long res;
    res = strtol(str, &end_ptr, 10);

    /* All number error handling are here to reduce boilerplate*/
    /* No dynamic memory allocation => no problems */
    if ((res == LONG_MAX && errno == ERANGE) || str == end_ptr || *end_ptr != '\0') {
        printf("Invalid argument '%s'\n", str);
        print_help();
        exit(2);
    }

    return res;
}

void argparse(int argc, char *argv[], long *start, long *stop, long *step) {
    switch (argc) {
        case 1:  /* No parameters */
            print_help();
            exit(0);
            break;
        case 2:  /* Only stop */
            *start = 0;
            *stop = get_number(argv[1]);
            *step = 1;
            break;
        case 3:  /* Start and stop */
            *start = get_number(argv[1]);
            *stop = get_number(argv[2]);
            *step = 1;
            break;
        case 4:  /* All parameters */
            *start = get_number(argv[1]);
            *stop = get_number(argv[2]);
            *step = get_number(argv[3]);
            break;
        default:  /* Too many parameters */
            printf("Error: Too many arguments\n\n");
            print_help();
            exit(1);
            break;
    }
}

void range_init(range *I) {
    I->curr = I->start;
}

int range_run(const range *I) {
    return I->curr < I->stop;
}

void range_next(range *I) {
    I->curr += I->step;
}

unsigned int range_get(const range *I) {
    return I->curr;
}

int main(int argc, char *argv[]) {
        range I;
        argparse(argc, argv, &I.start, &I.stop, &I.step);
        for(range_init(&I); range_run(&I); range_next(&I))
                printf("%d\n", range_get(&I));
        return 0;
}
