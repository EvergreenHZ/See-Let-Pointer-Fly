#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "avl.h"

AVLPtr avl_make_empty(AVLPtr root)
{
        if (root != NULL) {
                avl_make_empty(root->right);
                avl_make_empty(root->left);
                free(root);
        }
        return NULL;
}

/**
 * I won't consider the delete one
 */
NodePtr avl_find_max(AVLPtr root)
{
        if (root == NULL) {
                return NULL;
        }
        if (root->right == NULL) {
                return root;
        } else {
                return avl_find_max(root->right);
        }
}

NodePtr avl_find_min(AVLPtr root)
{
        if (root == NULL) {
                return NULL;
        }
        if (root->left == NULL) {
                return root;
        } else {
                avl_find_min(root->left);
        }
}

NodePtr avl_search(AVLPtr root, DataType data)
{
        if (root == NULL) {
                return NULL;
        }
        if (data == root->data) {
                return root;
        } else if (data > root->data) {
                return avl_search(root->left, data);
        } else {
                return avl_search(root->right, data);
        }
}

void avl_inorder_tranversal(AVLPtr root)
{
        if (root) {
                avl_inorder_tranversal(root->left);
                printf("%d ", root->data);
                avl_inorder_tranversal(root->right);
        }
        return ;
}

int avl_height(NodePtr root)
{
        if (root == NULL) {
                return -1;
        } else {
                return root->height;
        }
}

NodePtr avl_create_node(DataType data)
{
        NodePtr p = Malloc(sizeof(struct AVL));
        p->data = data;
        p->height = 0;
        p->left = NULL;
        p->right = NULL;

        return p;
}

/**
 * you have to program carefully
 */
static NodePtr single_rotation_with_right(NodePtr K2)
{
        NodePtr K1 = K2->left;
        K2->left = K1->right;
        K1->right = K2;

        K2->height = max(avl_height(K2->left),
                         avl_height(K2->right)) + 1;
        K1->height = max(avl_height(K1->left), K2->height) + 1;

        return K1;
}

static NodePtr single_rotation_with_left(NodePtr K1)
{
        NodePtr K2 = K1->right;
        K1->right = K2->left;
        K2->left = K1;

        K1->height = max(avl_height(K1->left),
                         avl_height(K1->right)) + 1;
        K2->height = max(avl_height(K2->right), K1->height) + 1;

        return K2;
}

static NodePtr double_roration_with_left_right(NodePtr K3)
{
        K3->left = single_rotation_with_left(K3->left);  // return, ok

        return single_rotation_with_right(K3);
}

static NodePtr double_roration_with_right_left(NodePtr K1)
{
        K1->right = single_rotation_with_right(K1->right);

        return single_rotation_with_left(K1);
}

NodePtr avl_insert(AVLPtr root, DataType data)
{
        if (root == NULL) {
               return avl_create_node(data);
        } else if (data < root->data) {  // go left
                root->left = avl_insert(root->left, data);
                if (avl_height(root->left) - avl_height(root->right) == 2) {  // find the first node losing balance
                        if (data < root->left->data) {  // insert left
                                root = single_rotation_with_right(root);
                        } else {
                                root = double_roration_with_left_right(root);
                        }
                }
        } else {
                root->right = avl_insert(root->right, data);
                if (avl_height(root->right) - avl_height(root->left) == 2) {
                        if (data > root->right->data) {  // insert right
                                root = single_rotation_with_left(root);
                        } else {
                                root = double_roration_with_right_left(root);
                        }
                }
        }
        root->height = max(avl_height(root->left), avl_height(root->right)) + 1;
        return root;
}
