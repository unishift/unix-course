#include "common.h"

int main()
{
    long *ai = 0;
    for (int i = 0; i < 10000; i++)
        buf_push(ai, i);
    TEST("size 10000", buf_size(ai) == 10000);
    int match = 0;
    for (int i = 0; i < (int) (buf_size(ai)); i++)
        match += ai[i] == i;
    TEST("match 10000", match == 10000);
    buf_free(ai);
}
