#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "common.h"


void Error(char *msg)
{
        printf("%s\n", msg);
        exit(-1);
}

void* Malloc(size_t num_of_mem_space)
{
        void *p = malloc(num_of_mem_space);
        if (p == NULL) {
                Error("malloc failed!\n");
        }

        return p;
}

int random_int()
{
        return rand();
}
