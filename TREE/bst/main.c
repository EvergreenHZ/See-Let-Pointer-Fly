#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bst.h"

int main()
{
        BSTPtr root = NULL;
        root = bst_random_construct(20);
        bst_inorder_tranversal(root);
        //root = bst_make_empty(root);

        ////int data[10] = {20, 17, 40, 18, 15, 36, 42, 19, 16, 35};
        //int data[10] = {42, 20, 17, 18, 15, 36, 40, 19, 16, 35};
        ////srand(time(NULL));
        //for (int i = 0; i < 10; i++) {
        //        //int data = rand() % 100;
        //        root = bst_insert(root, data[i]);
        //}
        //bst_print_root_leaf_path(root);

        //bst_print_pretty(root);

        //bst_inorder_tranversal(root); printf("\n");

        ////bst_delete_value3(root, 40);
        //root = bst_delete_value3(root, 20);
        //bst_inorder_tranversal(root); printf("\n");

        //printf("root->data is: %d\n", root->data);

        //root = bst_delete_value3(root, 35);
        //bst_inorder_tranversal(root); printf("\n");

        //printf("root->data is: %d\n", root->data);

        //root = bst_delete_value(root, 42);
        //bst_inorder_tranversal(root); printf("\n");
        //printf("root->data is: %d\n", root->data);

        //root = bst_delete_value(root, 17);
        //bst_inorder_tranversal(root); printf("\n");

        //root = bst_delete_value(root, 18);
        //bst_inorder_tranversal(root); printf("\n");

        bst_make_empty(root);

        return 0;
}
