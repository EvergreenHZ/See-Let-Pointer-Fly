#pragma once
#include "common.h"

typedef int DataType;

struct Node {
        DataType data;
        struct Node *prev;
        struct Node *next;
};

typedef struct Node* DList;
typedef struct Node* NodePtr;

void dlist_init(DList);

void dlist_destroy(DList);

void dlist_print(DList);

void dlist_reverse_print(DList);

enum Status dlist_insert_after(DList, NodePtr, DataType);

enum Status dlist_push_back(DList, DataType);

enum Status dlist_push_front(DList, DataType);

enum Status dlist_remove_after(DList, NodePtr);

enum Status dlist_pop_front(DList);

enum Status dlist_pop_back(DList);

enum Status dlist_remove_current(DList, NodePtr);

//enum Status dlist_remove_kth_node(DList, int);

NodePtr dlist_node_previous(DList, NodePtr);

NodePtr dlist_node_next(DList, NodePtr);

NodePtr dlist_at(DList, int);

NodePtr dlist_last_node(DList);

NodePtr dlist_find_key(DList, DataType);

int dlist_size(DList);

NodePtr dlist_create();

enum Status dlist_dispose(DList);
