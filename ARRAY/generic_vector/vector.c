#include "common.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void vector_init(Vector *vec, int num, char* type)
{
        if ( strcmp(type, "int") == 0) {
                vec->element_size = sizeof(int);
        } else if ( strcmp(type, "char") == 0) {
                vec->element_size = sizeof(char);
        }
        vec->capasity = num * vec->element_size;
        vec->buffer = Malloc(vec->capasity);
        vec->size = 0;
}
