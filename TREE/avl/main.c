#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "common.h"

int main()
{
        int data[10] = { 20, 17, 40, 18, 15, 36, 42, 19, 16, 35};

        NodePtr root = NULL;
        for (int i = 0; i < 10; i++) {
                root = avl_insert(root, data[i]);
        }

        avl_inorder_tranversal(root);
        printf("\n");
        return 0;
}
