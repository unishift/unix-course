#include <stdio.h>
#include <ctype.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)

void binsearch() {
    unsigned low = 1;
    unsigned high = 100;

    printf(_("Guess a number between (%u, %u): "), low, high);
    unsigned n;
    scanf("%u", &n);

    char answer;
    while (1) {
        const unsigned mid = (low + high) / 2;

        if (low == high) {
            printf(_("The number is %u!\n"), mid);
            break;
        }

        printf(_("Is number bigger than %u? (Y/N) "), mid);
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

int main() {
    setlocale(LC_ALL, "");
    bindtextdomain("binsearch", "./po");
    textdomain("binsearch");

    binsearch();
}