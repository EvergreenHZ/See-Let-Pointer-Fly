#pragma once
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

void *Malloc(size_t);

void Error(char *msg);

#define MAX(a, b) \
        (a) > (b) ? (a) : (b)

#define MIN(a, b) \
        (a) < (b) ? (a) : (b)

#define SWAP(a, b) \
        do { \
                int t = a; \
                a = b; \
                b = t; \
        } while(0)
