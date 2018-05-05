#pragma once

typedef int DataType;

/* let's not consider insert same data now 
 * and no deletion yet
 */
struct AVL {
        DataType data;
        struct AVL* left;
        struct AVL* right;
        int height;
};

typedef struct AVL AVL;
typedef struct AVL Node;
typedef struct AVL* AVLPtr;
typedef struct AVL* NodePtr;

AVLPtr avl_make_empty(AVLPtr );

NodePtr avl_find_max(AVLPtr);

NodePtr avl_find_min(AVLPtr);

NodePtr avl_search(AVLPtr, DataType);

NodePtr avl_insert(AVLPtr, DataType);

NodePtr avl_create_node(DataType data);

//NodePtr avl_find_parent(AVLPtr, NodePtr);

//void avl_lazy_delete(AVLPtr, DataType);

//void avl_print(AVLPtr);

void avl_inorder_tranversal(AVLPtr);

int avl_height(NodePtr);
