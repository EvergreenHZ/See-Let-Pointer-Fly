#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "dlist.h"

int main()
{
        struct Node dlist;  // dummy node
        dlist_init(&dlist);

        //if (dlist_remove_after(&dlist, NULL) == OK) {
        //        printf("ok, remove\n");
        //}
        //if (dlist_remove_current(&dlist, NULL) == OK) {
        //        printf("ok, remove current\n");
        //}

        for (int i = 0; i < 10; i++) {
                dlist_push_back(&dlist, i);
                //printf("size of list: %4d\n", dlist_size(&dlist));
                dlist_push_front(&dlist, 10 * (i + 1));
        }
        //dlist_print(&dlist);
        //printf("size of list: %4d\n\n", dlist_size(&dlist));
        //dlist_reverse_print(&dlist);

        for (int i = 0; i < 10; i++) {
                int r = random_int() % 20;
                printf("random r is: %4d     \n", r);
                NodePtr tmp = dlist_at(&dlist, r);
                //printf("tmp->data: %4d\n", tmp->data);
                //printf("tmp->prev->data: %4d\n", tmp->prev->data);
                //printf("position k: %4d\n", k);
                //dlist_remove_current(&dlist, dlist_at(&dlist, random_int()));
                dlist_remove_current(&dlist, tmp);
                printf("size of list: %4d\n", dlist_size(&dlist));
                dlist_print(&dlist);
                dlist_reverse_print(&dlist);
                printf("\n");
        }
        printf("size of list: %4d\n", dlist_size(&dlist));

        return 0;
}
