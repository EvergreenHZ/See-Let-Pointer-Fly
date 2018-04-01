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
        //printf("total number: %4d\n", nums);

        int i = 0;
        int j = 0;
        for (i = 0; i < nums; i++) {
                t_min = INT_MAX;
                for (j = 0; j < n; j++) {
                        if (p[j] && t_min > p[j]->data) {  // compare two numbers and select the little one
                                t_min = p[j]->data;
                                min_index = j;
                        }
                }
                //printf("min_index: %4d\n", min_index);
                list_push_back(dst, t_min);
                p[min_index] = p[min_index]->next;  // move to next
        }
        //printf("last: %4d\n", i);

        return STATUS_OK;
}
