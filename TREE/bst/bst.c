#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

BSTPtr bst_make_empty(BSTPtr root)
{
        if (root != NULL) {
                bst_make_empty(root->left);
                bst_make_empty(root->right);
                free(root);
        }
        return NULL;
}

NodePtr bst_find_max(BSTPtr root)
{
        if (root == NULL) {
                return NULL;
        } else if (root->right == NULL) {
                return root;
        } else {
                bst_find_max(root->right);
        }
}

NodePtr bst_find_min(BSTPtr root)
{
        if (root == NULL) {
                return NULL;
        } else if (root->left == NULL) {
                return root;
        } else {
                return bst_find_min(root->left);
        }
}

NodePtr bst_search(BSTPtr root, DataType data)
{
        if (root == NULL) {
                return NULL;
        } else if (data > root->data) {
                return bst_search(root->right, data);
        } else if (data < root->data) {
                return bst_search(root->left, data);
        } else {
                return root;
        }
}

/**
 * suppose no same data occurs
 */
NodePtr bst_insert(BSTPtr root, DataType data)
{
        if (root == NULL) {
                root= Malloc(sizeof(BST));
                root->data = data;
                root->left = NULL;
                root->right = NULL;
        }
        if (data > root->data) {
                root->right = bst_insert(root->right, data);
        } 
        if (data < root->data) {
                root->left = bst_insert(root->left, data);
        }
        return root;
}

NodePtr bst_insert2(BSTPtr root, DataType data)
{
        if (root == NULL) {
                root= Malloc(sizeof(BST));
                root->data = data;
                root->left = NULL;
                root->right = NULL;
                return root;
        }
        NodePtr p = root;
        NodePtr q = p;
        while (p) {
                q = p;
                if (data > root->data) {
                        p = p->right;
                } else if(data < root->data) {
                        p = p->left;
                } else {
                        return NULL;
                }
        }
        NodePtr new_node = Malloc(sizeof(BST));
        new_node->data = data;
        new_node->left = NULL;
        new_node->right = NULL;
        if (data > q->data) {
                q->right = new_node;
        } else {
                q->left = new_node;
        }
        return new_node;
}

NodePtr bst_find_parent(BSTPtr root, NodePtr node)
{
        if (root == NULL || node == NULL) {
                return NULL;
        }
        if (node == root) {
                return NULL;
        } else {
                NodePtr p = root;
                while (p) {  // node can't be root
                        if (p->left == node || p->right == node) {
                                printf("parent is: %d\n", p->data);
                                return p;
                        } else {
                                if (node->data > p->data) {
                                        p = p->right;
                                } else {
                                        p = p->left;
                                }
                        }
                }
                return NULL;
        }
}


static void bst_print_helper(BSTPtr root, int level)
{
        if (root == NULL) {
                return ;
        } else {
                for (int i = 0; i < level; i++) {
                        printf("\t");
                }
                printf("%d\n", root->data);
                bst_print_helper(root->left, level + 1);
                bst_print_helper(root->right, level + 1);
        }
}

void bst_print(BSTPtr root)
{
        if (root == NULL) {
                return ;
        } else {
                bst_print_helper(root, 0);
        }
}

void bst_inorder_tranversal(BSTPtr root)
{
        if (root == NULL) {
                return ;
        } else {
                bst_inorder_tranversal(root->left);
                printf("%d ", root->data);
                bst_inorder_tranversal(root->right);
        }
}

void bst_delete_value(BSTPtr root, DataType data)
{
       NodePtr node = bst_search(root, data);
       if (node == NULL) {
               return ;
       } else {
               bst_delete(root, node);
       }
}

BSTPtr bst_delete(BSTPtr root, NodePtr node)
{
        if (root == NULL) {
                return NULL;
        }
        if (node == root) {  // delete root
                if (node->left == NULL && node->right == NULL) {
                        free(node);
                        return NULL;
                        //return bst_make_empty(root);
                } else if (node->left == NULL && node->right != NULL) {
                        BSTPtr tmp_root = root->right;
                        free(root);
                        return tmp_root;
                } else if (node->left == NULL && node->right != NULL) {
                        BSTPtr tmp_root = root->left;
                        free(root);
                        return tmp_root;
                } else {
                        NodePtr right_min = bst_find_min(root->right);
                        int tmp_data = right_min->data;
                        bst_delete(root, right_min);
                        root->data = tmp_data;
                        printf("right min is: %d\n", tmp_data);
                        //free(right_min);
                        return root;
                }
        }
        NodePtr parent = bst_find_parent(root, node);
        if (node->left == NULL && node->right == NULL) {  // leaf node
                if (parent->left == node) {
                        parent->left = NULL;
                } else {
                        parent->right = NULL;
                }
                free(node);
                return root;
        } else if (node->left != NULL && node->right == NULL) {
                if (parent->left == node) {
                        parent->left = node->left;
                } else {
                        parent->right = node->left;
                }
                free(node);
                return root;
        } else if (node->left == NULL && node->right != NULL) {
                if (parent->left == node) {
                        parent->left = node->right;
                } else {
                        parent->right = node->right;
                }
                free(node);
                return root;
        } else {  // have two children
                NodePtr right_min = bst_find_min(node->right);
                int tmp_data = right_min->data;
                bst_delete(root, right_min);
                node->data = tmp_data;
        }
}
