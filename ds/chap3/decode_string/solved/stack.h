#pragma once

#include "vector.h"

typedef struct Vector StackInt;

#define stack_int_init vector_init

#define stack_int_destroy vector_destroy

#define stack_int_size vector_size

#define stack_int_empty(stack) ((stack)->size == 0)

#define stack_int_push vector_push_back

#define stack_int_peek(stack) (stack)->buffer[(stack)->size - 1]

ElementType stack_int_pop(StackInt *stack);
