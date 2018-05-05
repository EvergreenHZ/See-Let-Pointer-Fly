#include <stdio.h>
#include <stdlib.h>
#include "common.h"

void error(char *msg)
{
        printf("%s\n", msg);
        exit(-1);
}

void *Malloc(size_t size)
{
        void *p = malloc(size);
        if (p == NULL) {
                error("malloc failed!\n");
        }
        
        return p;
}

int max(int a, int b)
{
        return a > b ? a : b;
}
