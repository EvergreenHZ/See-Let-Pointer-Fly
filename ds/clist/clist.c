#include "clist.h"

#include <stdio.h>
#include <stdlib.h>

void clist_init(struct CList *list) {
        list->size = 0;
        list->head = NULL;
}

void clist_destroy(struct CList *list) {
        while (clist_size(list) > 0) {
                clist_remove_after(list, list->head);
        }
}

// TODO:
enum Status 
clist_insert_after(struct CList *list, struct CListNode *node, DataType data) {
        struct CListNode *p = (struct CListNode*)malloc(sizeof(struct CListNode));
        if (!p) return STATUS_ERR_ALLOC;
        p->data = data;
        p->next = node->next;
        node->next = p;
        list->size++;
        return STATUS_OK;
}

// TODO:
enum Status 
clist_remove_after(struct CList *list, struct CListNode *node) {
        if (list->size == 1) {
                free(node);
                list->head = NULL;
                list->size--;
        } else {
                struct CListNode *p = node->next->next;
                free(node->next);
                node->next = p;
                list->size--;
        }
        return STATUS_OK;
}

// Get list size
int clist_size(struct CList *list) { return list->size; }
