#pragma once
#include "common.h"

typedef int DataType;

struct Node {
        DataType data;
        struct Node *next;
};

typedef struct Node* List;
typedef struct Node* NodePtr;

void list_init(List);

void list_destroy(List);

NodePtr list_create();

void list_dispose(List);

void list_print(List);

void list_reverse(List);

void list_swap(List, List);

enum Status list_insert_after(List, NodePtr, DataType);

enum Status list_push_back(List, DataType);

enum Status list_push_front(List, DataType);

enum Status list_remove_after(List, NodePtr);

enum Status list_pop_front(List);

enum Status list_pop_back(List);

enum Status list_remove_current(List, NodePtr);

enum Status list_remove_kth_node(List, int);

enum Status list_remove_at(List, int);

NodePtr list_node_previous(List, NodePtr);

NodePtr list_node_next(NodePtr);

NodePtr list_at(List, int position);

NodePtr list_last_node(List);

NodePtr list_find_key(List, DataType);

int list_size(List);
