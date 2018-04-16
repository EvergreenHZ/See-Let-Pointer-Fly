#pragma once

#include "common.h"
#include "list.h"

typedef struct Node Vector;

#define vector_init list_init

#define vector_destroy list_destroy

#define vector_push_back list_push_back

#define vector_push_front list_push_front

#define vector_pop_back list_pop_back

#define vector_pop_front list_pop_front

#define vector_at list_at

#define vector_print list_print

#define vector_size list_size

#define vector_reverse list_reverse

#define vector_swap list_swap

#define vector_remove_at list_remove_at
