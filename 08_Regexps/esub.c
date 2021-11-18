#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <ctype.h>

#define MAX_MATCHES 10

void put_match(const char* string, const regmatch_t *regmatch) {
    for (regoff_t pos = regmatch->rm_so; pos < regmatch->rm_eo; pos++) {
        putchar(string[pos]);
    }
}

int main(int argc, char** argv) {
    if (argc != 4) {
        fprintf(stderr, "Invalid number of arguments\nUsage: %s regexp substitution string\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* regexp = argv[1];
    const char* substitution = argv[2];
    const char* string = argv[3];

    int return_code;
    regex_t regex_compiled;
    return_code = regcomp(&regex_compiled, regexp, REG_EXTENDED);
    if (return_code != 0) {
        char err_msg[100];
        regerror(return_code, &regex_compiled, err_msg, sizeof(err_msg));
        fprintf(stderr, "Cannot compile regexp: %s\n", err_msg);
        return EXIT_FAILURE;
    }

    regmatch_t regmatch[MAX_MATCHES];
    return_code = regexec(&regex_compiled, string, MAX_MATCHES, regmatch, 0);
    if (return_code != 0 && return_code != REG_NOMATCH) {
        char err_msg[100];
        regerror(return_code, &regex_compiled, err_msg, sizeof(err_msg));
        fprintf(stderr, "Cannot apply regexp: %s\n", err_msg);
        regfree(&regex_compiled);
        return EXIT_FAILURE;
    }

    int pos = 0;
    for (const char* ptr = string; *ptr != '\0'; ptr++, pos++) {
        if (return_code != REG_NOMATCH && pos == regmatch->rm_so) {
            ptr += regmatch->rm_eo - regmatch->rm_so - 1;

            for (const char *sptr = substitution; *sptr != '\0'; sptr++) {
                if (*sptr == '\\') {
                    sptr++;
                    if (*sptr == '\\') {
                        putchar(*sptr);
                    } else if (isdigit(*sptr)) {
                        const unsigned digit = *sptr - '0';
                        if (digit == 0) {
                            putchar('0');
                        } else {
                            put_match(string, regmatch + digit);
                        }
                    } else {
                        fprintf(stderr, "Incorrect substitution\n");
                        regfree(&regex_compiled);
                        return EXIT_FAILURE;
                    }
                } else {
                    putchar(*sptr);
                }
            }
        } else {
            putchar(*ptr);
        }
    }
    putchar('\n');
    regfree(&regex_compiled);
}
