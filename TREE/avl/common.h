#pragma once
#include <stddef.h>

void *Malloc(size_t);

void error(char *msg);

#define MAX(a, b) \
        (a) > (b) ? (a) : (b);

int max(int a, int b);

#define SWAP(a, b) \
        do { \
                int t = a; \
                a = b; \
                b = t; \
        } while(0)
