#pragma once 

#include "common.h"

typedef int DataType;

struct BST {
        DataType data;
        struct BST* left;
        struct BST* right;
};

typedef struct BST BST;
typedef struct BST Node;
typedef struct BST* BSTPtr;
typedef struct BST* NodePtr;

BSTPtr bst_make_empty(BSTPtr);

NodePtr bst_find_max(BSTPtr);

NodePtr bst_find_min(BSTPtr);

NodePtr bst_search(BSTPtr, DataType);

NodePtr bst_insert(BSTPtr, DataType);

NodePtr bst_insert2(BSTPtr, DataType);

NodePtr bst_find_parent(BSTPtr, NodePtr);

void bst_print(BSTPtr);

void bst_inorder_tranversal(BSTPtr);

BSTPtr bst_delete(BSTPtr, NodePtr);

void bst_delete_value(BSTPtr, DataType);
