#include "sorted_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


enum Status list_insert_before(struct List *list, struct ListNode *node,
                               DataType data)
{
        // if node is NULL, just append the node to list
        if (node == NULL) {
                return list_push_back(list, data);
        }

        // insert at the head of the list
        if (node == list->head) {
                return list_push_front(list, data);
        }
        
        // node is not NULL, search the list and find the right place
        struct ListNode *p = list->head;
        while (p) {
                if (p->next == node) {
                        return list_insert_after(list, p, data);
                }
                p = p->next;
        }

        return STATUS_ERR_INVALID_RANGE;  // anyway, return error
        /*
        struct ListNode *new_node = malloc(sizeof(struct ListNode));

        if (new_node == NULL) {
                return STATUS_ERR_ALLOC;
        }

        new_node->data = data;

        if (node == NULL) {
                // Insertion at the head of the list
                if (list_size(list) == 0) {  // empty list
                        list->tail = new_node;
                }

                new_node->next = list->tail;
                list->tail = new_node;
        } else {
                // Insertion at somewhere other than at the head
                struct ListNode *p = list->head;
                while (p) {
                        if (p->next == node) break;
                }
                new_node->next = node;
                p->next = new_node;
        }

        list->size++;*/

        //return STATUS_OK;
}

enum Status merge_sorted_lists(struct List *dst, struct List *src1,
                struct List *src2)
{
        // dst is a list, but may be empty
        struct ListNode* p = src1->head;
        struct ListNode* q = src2->head;
        //copy src1 to dst
        while (p) {
                list_push_back(dst, p->data);
                p = p->next;
        }

        // merge dst and src2
        for (int i = 0; i < src2->size; i++) {
                p = dst->head;
                for (int j = 0; j < dst->size; j++) {
                        if (p->data > q->data) {  // then insert before p
                                list_insert_before(dst, p, q->data);
                                break;
                        }
                        p = p->next;
                }
                if (p == NULL) {
                        list_push_back(dst, q->data);
                }
                q = q->next;
        }
}
