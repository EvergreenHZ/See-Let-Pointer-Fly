#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "btree.h"

struct BTree *btree_create(char data, TreePTr left, TreePTr right)
{
        BTree *root = Malloc(sizeof(struct BTree));
        root->data = data;
        root->left = left;
        root->right = right;

        return root;
}

void btree_destroy(TreePTr root)
{
        if (root == NULL) {
                return ;
        }
        btree_destroy(root->left);
        btree_destroy(root->right);
        free(root);
}

struct BTree* btree_from_pre_mid(char *pre, char *mid, int len)
{
        if (len == 0) {
                return NULL;
        }

        char *root = strchr(mid, pre[0]);  // find root
        if (root == NULL) {
                return NULL;
        }
        int ll = root - mid;  // length of left child

        TreePTr left = btree_from_pre_mid(pre + 1, mid, ll);  // left child tree
        TreePTr right = btree_from_pre_mid(pre + ll + 1, root + 1, len - ll - 1);

        return btree_create(*root, left, right);
}

/**
 * check https://siddontang.gitbooks.io/leetcode-solution/content/tree/construct_binary_tree.html
 */
struct BTree* btree_from_post_mid(char *post, char* mid, int len)
{
        if (len == 0) {
                return NULL;
        }

        char *root = strchr(mid, post[len - 1]);
        if (root == NULL) {
                return NULL;
        }
        int ll = root - mid;

        TreePTr left = btree_from_post_mid(post, mid, ll);
        TreePTr right = btree_from_post_mid(post + ll, root + 1, len - ll - 1);

        return btree_create(*root, left, right);
}

/**
 * check [here](https://www.geeksforgeeks.org/construct-tree-inorder-level-order-traversals/)
 * recursion version
 */
//int COUNT = 0;
char* extract_new_level(char *level, char *mid, int child_len, int length_of_level)
{
        //COUNT++;
        int i;
        char *tmp_mid = Malloc(sizeof(char) * (child_len + 1));
        strncpy(tmp_mid, mid, child_len);
        tmp_mid[child_len] = '\0';
        char *new_level = Malloc(sizeof(char) * (child_len + 1));
        int j = 0;
        for (i = 0; i < length_of_level; i++) {
                char *c = strchr(tmp_mid, level[i]);
                if (c) {
                        new_level[j++] = level[i];
                }
        }
        new_level[j] = '\0';
        //printf("%s      COUNT: %d\n", new_level, COUNT);
        return new_level;
}

struct BTree *btree_from_level_mid(char *level, char *mid, int len)
{
        if (len == 0) {
                return NULL;
        }
        char *root = strchr(mid, level[0]);
        if (root == NULL) {
                return NULL;
        }
        int ll = root - mid;
        char *left_level = 
                extract_new_level(level, mid, ll, len);
        char *right_level =
                extract_new_level(level, root + 1, len - ll - 1, len);

        struct BTree *left = 
                btree_from_level_mid(left_level, mid, ll);
        struct BTree *right = 
                btree_from_level_mid(right_level, root + 1, len - ll -1);
        // memory leak, free
        free(left_level);
        free(right_level);

        return btree_create(*root, left, right);
}

void btree_pre_order(struct BTree *root)
{
        if (root == NULL) {
                return ;
        }
        printf("%c", root->data);
        btree_pre_order(root->left);
        btree_pre_order(root->right);

        return ;
}

void btree_mid_order(struct BTree *root)
{
        if (root == NULL) {
                return ;
        }

        btree_mid_order(root->left);
        printf("%c", root->data);
        btree_mid_order(root->right);

        return ;
}

void btree_post_order(struct BTree *root)
{
        if (root == NULL) {
                return ;
        }

        btree_post_order(root->left);
        btree_post_order(root->right);
        printf("%c", root->data);
        return ;
}
/**
 * check [here](https://www.geeksforgeeks.org/print-level-order-traversal-line-line/)
 *
 * recursion version
 */
void print_given_level(struct BTree *root, int level)
{
        if (root == NULL) {
                return ;
        }
        if (level == 0) {
                printf("%c", root->data);
        }
        if (level > 0) {
                print_given_level(root->left, level - 1);
                print_given_level(root->right, level - 1);
        }
}

/**
 * https://www.geeksforgeeks.org/print-level-order-traversal-line-line/
 */
void btree_level_order(struct BTree *root)
{
        for (int i = 0; i < btree_depth(root); i++) {
                print_given_level(root, i);
        }
}

int btree_depth(struct BTree *root)
{
        if (root == NULL) {
                return 0;
        }

        return MAX(1 + btree_depth(root->left),\
                   1 + btree_depth(root->right));
}

int btree_leaves(struct BTree *root)
{
        if (root == NULL) {
                return 0;
        }
        if (!root->left && !root->right) {
                return 1;
        }
        return btree_leaves(root->left) + \
               btree_leaves(root->right);
}

void btree_flip(struct BTree *root)
{
        if (root == NULL) {
                return ;
        }

        TreePTr tmp = root->left;
        root->left = root->right;
        root->right = tmp;

        btree_flip(root->left);
        btree_flip(root->right);

        return ;
}

/**
 * check https://www.crondose.com/2016/06/create-a-binary-search-tree-array/
 */
struct BTree *btree_build_search_tree(char s[])
{
        if (s) {
                TreePTr root = Malloc(sizeof(BTree));
                root->data = s[0];
                root->left = NULL;
                root->right = NULL;
                int n;
                for (n = 0; s[n] != '\0'; n++)
                        ;
                for (int i = 1; i < n; i++) {
                        char data = s[i];
                        TreePTr node = Malloc(sizeof(BTree));
                        node->data = data;
                        node->left = NULL;
                        node->right = NULL;
                        
                        NodePtr p = root;
                        NodePtr q;  // remember p
                        while (p) {
                                q = p;
                                if (p->data > data) {
                                        p = p->left;
                                } else {
                                        p = p->right;
                                }
                        }
                        if (q->data > data) {
                                q->left = node;
                        } else {
                                q->right = node;
                        }
                }
                return root;
        }
        return NULL;
}

struct BTree *btree_find(struct BTree*root, char value)
{
        if (root) {
                if (root->data == value) {
                        return root;
                }
                if (value > root->data) {  // go right
                        return btree_find(root->right, value);
                } else {
                        return btree_find(root->left, value);
                }
        }
        return NULL;
}

/**
 * https://www.geeksforgeeks.org/write-c-code-to-determine-if-two-trees-are-identical/
 * https://www.geeksforgeeks.org/check-two-bsts-contain-set-elements/
 */
int btree_is_same(struct BTree *a, struct BTree *b)
{
        if (!a && !b) {
                return 1;
        } else if (a && b) {
                return ( (a->data == b->data) &&
                         btree_is_same(a->left, b->left) &&
                         btree_is_same(a->right, b->right));
        }
        return 0;
}

/**
 * https://www.geeksforgeeks.org/tree-isomorphism-problem/
 */
int btree_is_isomorphic(struct BTree *a, struct BTree *b)
{
        if (!a && !b) {
                return 1;
        } else if (a && b) {
                return ( (a->data == b->data) &&
                         ((btree_is_isomorphic(a->left, b->left) &&
                          btree_is_isomorphic(a->right, b->right)) ||

                          (btree_is_isomorphic(a->left, b->right) &&
                           btree_is_isomorphic(a->right, b->left))));
        }
        return 0;
}
