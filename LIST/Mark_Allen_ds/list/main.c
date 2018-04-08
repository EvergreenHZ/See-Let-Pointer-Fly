#include <stdio.h>
#include "list.h"

int main()
{
        struct Node list;  // a dummy node
        list_init(&list);

        if (list_pop_front(&list) == OK) {
                printf("pop front empty list, ok!\n");
        }
        if (list_pop_back(&list) == OK) {
                printf("pop back empty list, ok!\n");
        }
        if (list_remove_current(&list, NULL) == OK) {
                printf("remove current empty list, ok!\n");
        }

        for (int i = 0; i < 10; i++) {
                list_push_back(&list, i);
        }
        list_print(&list);

        for (int i = 2; i < 5; i++) {
                list_remove_kth_node(&list, i);
        }
        list_print(&list);

        for (int i = 7; i < 12; i++) {
                list_push_front(&list, i);
                list_pop_back(&list);
        }
        list_print(&list);

        return 0;
}
