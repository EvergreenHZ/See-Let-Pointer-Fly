#pragma once

#include "list.h"

typedef struct Node Stack;

#define stack_init list_init

#define stack_destroy list_destroy

#define stack_push list_push_front

#define stack_size list_size

DataType stack_peek(Stack *);

DataType stack_pop(Stack *);
