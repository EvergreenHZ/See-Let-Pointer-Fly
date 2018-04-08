#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* 
 * be careful when inserting or removing a node
 * say append, push_front, pop etc.
 *
 */
void list_init(struct List *list)
{
        list->size = 0;
        list->head = NULL;
        list->tail = NULL;
}

void list_destroy(struct List *list)
{
        struct ListNode *node = list->head;
        struct ListNode *tmp;
        while(node) {
                tmp = node->next;
                free(node);
                node = tmp;
        }
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
}

enum Status list_insert_after(struct List *list, struct ListNode *node,
                DataType data)
{
        struct ListNode *inserted_node = (struct ListNode*)malloc(sizeof(struct ListNode));
        if (!inserted_node) return STATUS_ERR_ALLOC;

        inserted_node->data = data;
        inserted_node->next = NULL;

        if (!list->head) {  // empty list
                list->head = inserted_node;
                list->tail = inserted_node;
                list->size++;
        } else if (!node) {
                //insert at the head of the list and it's not empty
                inserted_node->next = list->head;
                list->head = inserted_node;
                list->size++;
        } else if (node == list->tail) {  // append
                node->next = inserted_node;
                list->tail = inserted_node;
                list->size++;
        } else {  // common place
                inserted_node->next = node->next;
                node->next = inserted_node;
                list->size ++;
        }
        return STATUS_OK;
}
enum Status list_push_back(struct List *list, DataType data)
{
        return list_insert_after(list, NULL, data);
}

enum Status list_push_front(struct List *list, DataType data)
{
        struct ListNode *p = malloc(sizeof(struct ListNode));
        if (!p) return STATUS_OK;
        p->data = data;
        p->next = NULL;
        if (list->head == NULL) {  // empty list
                list->head = p;
                list->tail = p;
                list->size++;
        } else {
                p->next = list->head;
                list->head = p;
                list->size++;
        }
        return STATUS_OK;
}

/* remove the node after node, which means the list is not empty */
enum Status list_remove_after(struct List *list, struct ListNode *node)
{
        if (node == list->tail) {
                return STATUS_OK;
        } else {
                struct ListNode *tmp = node->next;
                node->next = node->next->next;
                free(tmp);
                list->size--;
        }
        return STATUS_OK;
}

enum Status list_pop_front(struct List *list)
{
        if (list->head) {
                struct ListNode *tmp = list->head;
                list->head = tmp->next;
                free(tmp);
                list->size--;
                return STATUS_OK;
        }
        return STATUS_ERR;
}

int list_size(struct List* list)
{
        return list->size;
}

struct ListNode *list_at(struct List *list, int i)
{
        int n = 0;
        struct ListNode *node = list->head;
        while(node) {
                if (n++ == i) return node;
                node = node->next;
        }
        return NULL;
}
