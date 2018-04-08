#include "list.h"
#include "sorted_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void print_list(struct List *list) {
        struct ListNode *p = list->head;

        while (p) {
                printf("%d ", p->data);
                p = p->next;
        }

        printf("\n");
}

int main() {

        srand(time(NULL));

        struct List *srcs[11], dst;
        list_init(&dst);
        for (int i = 0; i < 10; i ++) {
                srcs[i] = (struct List*)malloc(sizeof(struct List));
        }

        for (int i = 0; i < 10; i++) {
                list_init(srcs[i]);
                for (int j = 0; j < 5 + 2 * i; j++) {
                        list_push_back(srcs[i], i * (j + 1) + 1 + j);
                }
                print_list(srcs[i]);
        }


        merge_multiple_lists(&dst, srcs, 10);
        print_list(&dst);
        

        return 0;
}
