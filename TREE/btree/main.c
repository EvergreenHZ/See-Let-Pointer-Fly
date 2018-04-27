
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "btree.h"

int main() {
        char *pre = "ABCDEFGHIJKL";
        char *mid = "CBEFDGAJIKLH";
        char *post = "CFEGDBJLKIHA";
        char *level = "ABHCDIEGJKFL";

        struct BTree *root = btree_from_pre_mid(pre, mid, strlen(pre));
        struct BTree *b = btree_from_level_mid(level, mid, 12);
        if (btree_is_same(root, b)) {
                printf("same\n");
        } else {
                printf("diff\n");
        }
        //struct BTree *root = btree_build_search_tree(level);
        //struct BTree *found_node = btree_find(root, 'E');
        //putchar(found_node->data);
        //putchar('\n');

        //struct BTree *root = btree_from_post_mid(post, mid, strlen(pre));
        //btree_pre_order(root);
        //btree_level_order(root);
        //printf("\n");
        btree_mid_order(root);
        //printf("\n");
        //btree_post_order(root);
        putchar('\n');

        printf("%d leaves\n", btree_leaves(root));

        btree_destroy(root);
}
