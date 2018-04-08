#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

void vector_realloc(struct vector *vec)
{
        int *p = (int *)realloc(vec->data, vec->capacity * 2 * sizeof(int));
        if (!p) {
                printf("realloct failed!\n");
                return ;
        }
        vec->data = p;
        vec->capacity *= 2;
}

void vector_new(struct vector *vec, int cap)
{
        if (cap <= 0) {
                printf("wrong capacity");
                return ;
        }

        vec->data = (int *) malloc(cap * sizeof(int));
        if (!vec->data) {
                printf("vector_new failed!");
        }

        vec->capacity = cap;
        vec->size     = 0;
}

void vector_destory(struct vector *vec)
{
        if (vec->data) {
                free(vec->data);
                vec->data     = NULL;
                vec->capacity = 0;
                vec->size     = 0;
        }
}

void vector_print(struct vector *vec)
{
        for (int i = 0; i < vec->size; i++) {
                printf("%4d ", vec->data[i]);
        }
        printf("\n");
}

void vector_insert(struct vector *vec, int pos, int value)
{
        // pos 0, 1, ... , size - 1, size
        if (pos < 0 || pos > vec->size) {
                printf("wrong postion\n");
                return ;
        }

        if (vec->size == vec->capacity) {
                vector_realloc(vec);
        }

        for (int i = vec->size; i > pos; i--) {
                vec->data[i] = vec->data[i - 1];
        }

        vec->data[pos] = value;
        vec->size ++;
        return ;
}

void vector_push_back(struct vector *vec, int value)
{
        vector_insert(vec, vec->size, value);
}

void vector_push_front(struct vector *vec, int value)
{
        vector_insert(vec, 0, value);
}

void vector_remove_at(struct vector *vec, int pos)
{
        if (pos < 0 || pos > vec->size - 1) {
                printf("wrong postion\n");
                return ;
        }

        for (int i = pos + 1; i < vec->size; i++) {
                vec->data[i - 1] = vec->data[i];
        }
        vec->size --;
}

void vector_pop_front(struct vector *vec)
{
        vector_remove_at(vec, 0);
}

void vector_pop_back(struct vector *vec)
{
        vector_remove_at(vec, vec->size);
}

int vector_find_first(struct vector *vec, int value)
{
        int *p = vec->data;
        while (p != vec->data + vec->size) {
                if (*p++ == value)
                        return p - vec->data - 1;
        }

        return -1;
}

int vector_find_next(struct vector *vec, int value, int start_pos)
{
        if (!vec->size) return -1;

        if (start_pos > vec->size - 1 || start_pos < 0) {
                return -1;  // wrong position
        }

        int *p = vec->data + start_pos;
        while (p != vec->data + vec->size) {
                if (*p++ == value)
                        return p - vec->data - 1;
        }

        return -1;  // not found
}

void vector_delete_value(struct vector *vec, int value)
{
        for (int i = 0; i < vec->size; i++)
                if (vec->data[i] == value)
                        vector_remove_at(vec, i);
}

void vector_union(struct vector *c, struct vector *a, struct vector *b)
{
        //
        return ;
}

void vector_reverse(struct vector *vec)
{
        if (vec->data) {
                int first, last;
                for (first = 0, last = vec->size - 1; first < last; first++, last--) {
                        vec->data[first] ^= vec->data[last];
                        vec->data[last]  ^= vec->data[first];
                        vec->data[first] ^= vec->data[last];
                }
        }
}

void vector_swap(struct vector *a, struct vector *b)
{
        struct vector tmp;
        tmp = *a;
        *a  = *b;
        *b  = tmp;
}

void vector_shrink_to_fit(struct vector *vec)
{
        if (vec->size) {
                int *tmp = (int*)malloc(vec->size * sizeof(int));

                for (int i = 0; i < vec->size; i++) {
                        tmp[i] = vec->data[i];
                }
                free(vec->data);  // xxx
                vec->data = tmp;
                vec->capacity = vec->size;
        }
}

int at(struct vector *vec, int index)
{
        if (vec->size && vec->data) {
                return (index %= vec->size) < 0 ? vec->data[vec->size + index] : vec->data[index];
        } else {
                exit(-1);
        }
}
