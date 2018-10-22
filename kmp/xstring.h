#pragma once

#include "common.h"
//int* naive_matcher()

typedef struct xstring {
        char* T;  // text string

        //void (func_destroy*)(char*);
} xstring;

void string_init(xstring*, int);

//void destroy(char*);

//bool naive_matcher(xstring* T, xstring* P);

bool kmp_matcher(xstring* T, xstring* P);
