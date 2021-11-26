#include "common.h"

int main() {
    float *a = 0;
    buf_clear(a);
    TEST("clear empty", buf_size(a) == 0);
    TEST("clear no-op", a == 0);
}