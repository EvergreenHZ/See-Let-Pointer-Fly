#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bst.h"

int main()
{
        BSTPtr root = NULL;
        bst_make_empty(root);

        int data[10] = {20, 17, 40, 18, 15, 36, 42, 19, 16, 35};
        //srand(time(NULL));
        for (int i = 0; i < 10; i++) {
                //int data = rand() % 100;
                root = bst_insert(root, data[i]);
        }

        bst_inorder_tranversal(root); printf("\n");

        bst_delete_value(root, 20);
        bst_inorder_tranversal(root); printf("\n");

        bst_delete_value(root, 17);
        bst_inorder_tranversal(root); printf("\n");

        bst_delete_value(root, 18);
        bst_inorder_tranversal(root); printf("\n");
        
        //bst_make_empty(root);

        return 0;
}
