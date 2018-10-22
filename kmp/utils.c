#include "common.h"

void Error(char* msg)
{
        printf("%s\n", msg);
        exit(-1);
}

void* Malloc(size_t len)
{
        void* p = malloc(sizeof(len));
        if (!p) {
                printf("Malloc Failed!");
                exit(-1);
        }
        return p;
}

int rand_int(int module)
{
        srand(time(NULL));

        return rand() % module;
}

void Log(char *msg)
{
        printf("%s\n", msg);
}

void print_array(int *A, int len)
{
        if (len <= 0) return;
        for (int i = 0; i < len; i++) {
                printf("%d ", A[i]);
        }
        printf("\n");
}
