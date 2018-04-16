#include <stdio.h>
#include "list.h"

void gen_list(List list, int num)
{
        for (int i = 0; i < num; i++) {
                list_push_back(list, i);
        }
}

void print_P_on_L(List L, List P)
{
        int size_l = list_size(L);
        printf("%4d \n", size_l);
        NodePtr p = P->next;
        int i = 0;
        while (p) {
                int pos = p->data % size_l;
                pos = (pos <= 0) ? -pos : pos;
                //printf("%4d \n", pos);
                NodePtr node = list_at(L, pos);
                if (!node) {
                        p = p->next;
                        continue;
                }
                //printf("%4d ", node->data);
                p = p->next;
                printf("%d\n", i++);
        }
        printf("\n");
        return ;
}

int main()
{
        //NodePtr L = list_create();
        //NodePtr P = list_create();
        struct Node L, P;
        list_init(&L);
        list_init(&P);

        gen_list(&L, 5);
        gen_list(&P, 5);
        //list_print(&L);
        //list_print(&P);

        print_P_on_L(&L, &P);


        //struct Node list;  // a dummy node
        //list_init(&list);

        //if (list_pop_front(&list) == OK) {
        //        printf("pop front empty list, ok!\n");
        //}
        //if (list_pop_back(&list) == OK) {
        //        printf("pop back empty list, ok!\n");
        //}
        //if (list_remove_current(&list, NULL) == OK) {
        //        printf("remove current empty list, ok!\n");
        //}

        //for (int i = 0; i < 10; i++) {
        //        list_push_back(&list, i);
        //}
        //list_print(&list);

        //list_reverse(&list);

        //for (int i = 2; i < 5; i++) {
        //        list_remove_kth_node(&list, i);
        //}
        //list_print(&list);

        //for (int i = 7; i < 12; i++) {
        //        list_push_front(&list, i);
        //        list_pop_back(&list);
        //}
        //list_print(&list);

        //list_destroy(&list);

        //NodePtr dummy_head = list_create();
        //for (int i = 0; i < 10; i++) {
        //        list_push_back(dummy_head, i);
        //}
        //list_print(dummy_head);
        //list_dispose(dummy_head);

        return 0;
}
