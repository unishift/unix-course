#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <libintl.h>
#include <locale.h>
#include <getopt.h>

#define _(STRING) gettext(STRING)

void print_help(int use_md) {
    const char* description = _("This program does binary search with manual input.");
    const char* prog_arguments = _("Program arguments");
    const char* help_strings[][2] = {
        {"-r", _("Use roman numbers for printing")},
        {"--help", _("Show this help message")},
        {"--help-md", _("Show help message in markdown format")},
        {NULL, NULL}
    };

    if (use_md) {
        printf("## Description\n");
        printf("%s\n", description);
        printf("## Usage\n");
        printf("%s:\n", prog_arguments);
        for (int i = 0; help_strings[i][0] != NULL; i++) {
            printf("- `%s`\t%s\n", help_strings[i][0], help_strings[i][1]);
        }
    } else {
        printf("%s\n", description);
        printf("%s:\n", prog_arguments);
        for (int i = 0; help_strings[i][0] != NULL; i++) {
            printf("%s - %s\n", help_strings[i][0], help_strings[i][1]);
        }
    }
}

static const char* to_roman[] = {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII", "XIII", "XIV", "XV", "XVI", "XVII", "XVIII", "XIX", "XX", "XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII", "XXIX", "XXX", "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII", "XXXVIII", "XXXIX", "XL", "XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII", "XLIX", "L", "LI", "LII", "LIII", "LIV", "LV", "LVI", "LVII", "LVIII", "LIX", "LX", "LXI", "LXII", "LXIII", "LXIV", "LXV", "LXVI", "LXVII", "LXVIII", "LXIX", "LXX", "LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV", "LXXVI", "LXXVII", "LXXVIII", "LXXIX", "LXXX", "LXXXI", "LXXXII", "LXXXIII", "LXXXIV", "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX", "XC", "XCI", "XCII", "XCIII", "XCIV", "XCV", "XCVI", "XCVII", "XCVIII", "XCIX", "C"};

/**
 * Function to print number in roman format
 *
 * @param num number to print
 */
void print_roman(unsigned num) {
    printf("%s", to_roman[num - 1]);
}

/**
 * Function to convert number in roman format to normal
 *
 * @param roman roman formatted number
 * @return number in normal format
 */
unsigned from_roman(const char* roman) {
    for (unsigned i = 0; i < 101; i++) {
        if (strcmp(to_roman[i], roman) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * Main binary search function
 *
 * @param use_roman Whether to use roman numbers instead of normal ones
 */
void binsearch(int use_roman) {
    unsigned low = 1;
    unsigned high = 100;

    printf("%s (%u, %u): ", _("Guess a number between"), low, high);
    unsigned n;
    scanf("%u", &n);

    char answer;
    while (1) {
        const unsigned mid = (low + high) / 2;

        if (low == high) {
            printf("%s ", _("The number is"));
            if (use_roman) {
                print_roman(mid);
            } else {
                printf("%u", mid);
            }
            printf("!\n");
            break;
        }

        printf("%s ", _("Is number bigger than"));
        if (use_roman) {
            print_roman(mid);
        } else {
            printf("%u", mid);
        }
        printf("? (Y/N) ");
        int res = scanf(" %c", &answer);
        if (res == 0 || res == EOF || (tolower(answer) != 'y' && tolower(answer) != 'n')) {
            continue;
        }

        if (tolower(answer) == 'y') {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "");
    bindtextdomain("binsearch", "./po");
    textdomain("binsearch");

    int use_roman = 0;

    /* Parse arguments */
    while (1) {
        static struct option long_options[] =
            {
                {"help",     no_argument,       0, 'h'},
                {"help-md",     no_argument,       0, 'm'},
                {0, 0, 0, 0}
            };
        int option_index = 0;

        int c = getopt_long(
            argc, argv, "rhm",
            long_options, &option_index
        );

        if (c == -1) {
            break;
        }

        switch (c) {
        case 'r':
            use_roman = 1;
            break;
        case 'h':
            print_help(0);
            return 0;
        case 'm':
            print_help(1);
            return 0;
        default:
            return 1;
        }
    }

    binsearch(use_roman);
}