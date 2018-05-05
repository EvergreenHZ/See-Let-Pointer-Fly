#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
                                //printf("parent is: %d\n", p->data);
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

BSTPtr bst_delete_value(BSTPtr root, DataType data)
{
       NodePtr node = bst_search(root, data);
       if (node == NULL) {
               return NULL;
       } else {
               return bst_delete(root, node);
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
                } else if (node->left != NULL && node->right == NULL) {
                        BSTPtr tmp_root = root->left;
                        free(root);
                        return tmp_root;
                } else {
                        NodePtr right_min = bst_find_min(node->right);
                        int tmp_data = right_min->data;
                        // cause I always pass the root
                        bst_delete(root, right_min);
                        node->data = tmp_data;
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
                return root;
        }
}

BSTPtr bst_delete2(BSTPtr root, DataType data)
{
        NodePtr tmp_cell;
        if (root == NULL) {
                return NULL;
        } else if (data < root->data) {  // go left
                root->left = bst_delete2(root->left, data);
        } else if (data > root->data) {  // go right
                root->right = bst_delete2(root->right, data);
        } else {  // data found and delete
                if (root->left && root->right) {  // two children
                        tmp_cell = bst_find_min(root->right);
                        root->data = tmp_cell->data;
                        root->right = bst_delete2(root->right, tmp_cell->data);
                } else {  // one or zore children
                        tmp_cell = root;
                        if (root->left == NULL) {
                                root = root->right;  // you will return root
                        } else {
                                if (root->right == NULL) {
                                        root = root->left;
                                }
                        }
                        free(tmp_cell);
                }
        }
        return root;
}

BSTPtr bst_delete3(BSTPtr root, NodePtr node)
{
        if (root == NULL) {
                return NULL;
        }
        if (node == root) {  // delete root
                if (node->left == NULL && node->right == NULL) {
                        free(node);
                        return NULL;
                } else if (node->left == NULL && node->right != NULL) {
                        BSTPtr tmp_root = root->right;
                        free(root);
                        return tmp_root;
                } else if (node->left != NULL && node->right == NULL) {
                        BSTPtr tmp_root = root->left;
                        free(root);
                        return tmp_root;
                } else {  // have both left and right children
                        NodePtr right_min = bst_find_min(node->right);
                        root->data = right_min->data;
                        // right_min has no left child
                        node->right = bst_delete(node->right, right_min);
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
                node->data = right_min->data;
                node->right = bst_delete(node->right, right_min);
                return root;
        }
}

BSTPtr bst_delete_value3(BSTPtr root, DataType data)
{
       NodePtr node = bst_search(root, data);
       if (node == NULL) {
               return NULL;
       } else {
               // pass value, cause you don't delete root unless ...
               NodePtr tmp = bst_delete3(root, node);
               //printf("tmp root: %d\n", tmp->data);
               return tmp;
       }
}

//#define COUNT 10
//static void bst_print_helper2(BSTPtr root, int space)
//{
//        if (root == NULL) {
//                return ;
//        }
//        space += COUNT;
//        bst_print_helper(root->right, space);
//
//        printf("\n");
//        for (int i = COUNT; i < space; i++) {
//                printf(" ");
//        }
//        printf("%d\n", root->data);
//
//        bst_print_helper(root->left, space);
//}
//
//void bst_print_pretty(BSTPtr root)
//{
//        bst_print_helper2(root, 0);
//}
static void print_array(int path[], int len)
{
        for (int i = 0; i < len; i++) {
                printf("%d ", path[i]);
        }
        printf("\n");
}

static void print_paths_recur(BSTPtr root, int path[], int len)
{
        if (root == NULL) {
                return ;
        }
        path[len] = root->data;
        if (!root->left && !root->right) {
                print_array(path, len + 1);
        } else {
                print_paths_recur(root->left, path, len + 1);
                print_paths_recur(root->right, path, len + 1);
        }
}


void bst_print_root_leaf_path(BSTPtr root)
{
        int path[1000];
        print_paths_recur(root, path, 0);
}

NodePtr bst_random_construct(int number_of_nodes)
{
        srand(time(NULL));
        NodePtr root = NULL;
        while (number_of_nodes--) {
                root = bst_insert(root, rand());
        }
        return root;
}
