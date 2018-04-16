#include "common.h"

//typedef union ElementSize {
//        size_t element_int;
//        size_t element_char;
//} ElementSize;

struct DataPointer {
        char *pchar;
        int *pint;
        double *pdouble;
};

/*
 * (*(&dp + k * sizeof(void*)))
 */

typedef struct Vector {
        int size;
        int capasity;
        void *buffer;
        size_t element_size;
        DataPointer dp;
} Vector;

#define VECTOR_INIT(vec, num, type) vector_init(vec, num,  #type)
void vector_init(Vector*, int, char*);

//void vector_destroy(Vector*);

