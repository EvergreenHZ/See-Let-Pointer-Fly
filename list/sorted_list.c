#include "sorted_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// TODO:
enum Status merge_sorted_lists(struct List *dst, struct List *src1,
                struct List *src2)
{
        struct ListNode *p, *q;
        p = src1->head;
        q = src2->head;
        for (int i = 0; i < src1->size + src2->size; i++) {
                if (p && q && p->data < q->data) {  // this is ok
                        list_push_back(dst, p->data);
                        p = p->next;
                } else {
                        list_push_back(dst, q->data);
                        q = q->next;
                }
        }
        return STATUS_OK;
}

// TODO:
enum Status merge_multiple_lists(struct List *dst, struct List **srcs, int n)
{
        struct ListNode ** p = (struct ListNode **) malloc(sizeof(struct ListNode *) * n);
        int nums = 0;  // number of total numbers
        DataType t_min;
        int min_index = 0;
        for (int i = 0; i < n; i++) {
                nums += srcs[i]->size;
                p[i] = srcs[i]->head;  // copy all list head
        }

        for (int i = 0; i < nums; i++) {
                for (int j = 0; j < n - 1; j++) {
                        if (p[i] && p[i]->data < p[i + 1]->data) {  // compare two numbers and select the little one
                                t_min = p[i]->data;
                                min_index = i;
                        }
                }
                list_push_back(dst, t_min);
                p[min_index] = p[min_index]->next;  // move to next
        }

        return STATUS_OK;
}
