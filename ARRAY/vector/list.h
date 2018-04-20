#pragma once

#include "common.h"

typedef int DataType;

struct ListNode {
        DataType data;
        struct ListNode *next;
};

struct List {
        int size;
        struct ListNode *head;
        struct ListNode *tail;
};

typedef struct ListNode ListNode;
typedef struct List     List;
typedef struct List*    ListPtr;
typedef struct ListNode* NodePtr;

/* construction and destroy */
void list_init(ListPtr);

void list_destroy(ListPtr);

ListPtr list_create();

void list_dispose(ListPtr);

/* common methods */
enum Status list_insert_after(ListPtr, NodePtr, DataType);

enum Status list_push_back(ListPtr, DataType);

enum Status list_push_front(ListPtr, DataType);

enum Status list_remove_after(ListPtr, NodePtr);

enum Status list_pop_front(ListPtr);

enum Status list_pop_back(ListPtr);

int list_size(ListPtr);

NodePtr list_at(ListPtr, int);

void list_print(ListPtr);

void list_reverse(ListPtr);

void list_swap(ListPtr, ListPtr);

NodePtr list_last_node(ListPtr);

NodePtr list_find_key(ListPtr, DataType);

enum Status list_remove_current(ListPtr, NodePtr);

enum Status list_remove_kth_node(ListPtr, int);

//enum Status list_remove_at(ListPtr, NodePtr);

NodePtr list_node_previous(ListPtr, NodePtr);

NodePtr list_node_next(ListPtr, NodePtr);
