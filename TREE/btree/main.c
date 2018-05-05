
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "btree.h"

//void help()
//{
//        printf("please input suffix expression:\n");
//}
//
//char* parse_string(const char* s, int len)
//{
//        int input = Malloc(len* sizeof(char));
//        int count = 0;
//        for (int i = 0; i < len; i ++ ) {
//                if (s[i] == ' ') {
//                        continue;
//                } else {
//                        input[count++] = s[i];
//                }
//        }
//        input[count] = '\0';
//        return input;
//}
//
//void construct_expression_tree(const char* s)
//{
//        while (s[i] != '\0') {



int main() {
        //help();
        //const char *s = "a b + c d e + * *";
        //int len = sizeof(s) / sizeof(char);
        //char *input = parse_string(s, len);
        //construct_expression_tree(input);
        //char *pre = "ABCDEFGHIJKL";
        //char *mid = "CBEFDGAJIKLH";
        //char *post = "CFEGDBJLKIHA";
        //char *level = "ABHCDIEGJKFL";

        //struct BTree *root = btree_from_pre_mid(pre, mid, strlen(pre));
        //struct BTree *b = btree_from_level_mid(level, mid, 12);
        //if (btree_is_same(root, b)) {
        //        printf("same\n");
        //} else {
        //        printf("diff\n");
        //}
        ////struct BTree *root = btree_build_search_tree(level);
        ////struct BTree *found_node = btree_find(root, 'E');
        ////putchar(found_node->data);
        ////putchar('\n');

        ////struct BTree *root = btree_from_post_mid(post, mid, strlen(pre));
        ////btree_pre_order(root);
        ////btree_level_order(root);
        ////printf("\n");
        //btree_mid_order(root);
        ////printf("\n");
        ////btree_post_order(root);
        //putchar('\n');

        //printf("%d leaves\n", btree_leaves(root));

        //btree_destroy(root);
}
