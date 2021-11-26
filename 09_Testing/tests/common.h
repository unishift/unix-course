#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdint.h>
#include <setjmp.h>

static jmp_buf escape;

#define BUF_ABORT test_abort()
#include "buf.h"

#if _WIN32
#  define C_RED(s)     s
#  define C_GREEN(s)   s
#else
#  define C_RED(s)     "\033[31;1m" s "\033[0m"
#  define C_GREEN(s)   "\033[32;1m" s "\033[0m"
#endif

#define TEST(s, x) \
    do { \
        if (x) { \
            printf(C_GREEN("PASS") " %s\n", s); \
        } else { \
            printf(C_RED("FAIL") " %s\n", s); \
            exit(1); \
        } \
    } while (0)

#endif //COMMON_H
