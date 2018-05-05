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

BSTPtr bst_delete(BSTPtr, NodePtr);

BSTPtr bst_delete2(BSTPtr, DataType);

BSTPtr bst_delete3(BSTPtr, NodePtr);

BSTPtr bst_delete_value(BSTPtr, DataType);

BSTPtr bst_delete_value3(BSTPtr, DataType);

void bst_print(BSTPtr);

void bst_inorder_tranversal(BSTPtr);

//void bst_print_pretty(BSTPtr);

void bst_print_root_leaf_path(BSTPtr);

NodePtr bst_random_construct(int number_of_nodes);
