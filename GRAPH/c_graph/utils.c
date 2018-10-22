#include "common.h"

void Error(char *msg)
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
