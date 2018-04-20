#include "list.h"
#include <stdio.h>
#include <stdlib.h>


void list_init(ListPtr list)
{
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
}

void list_destroy(ListPtr list)
{
        NodePtr node = list->head;
        while (node) {
                NodePtr tmp = node->next;
                free(node);
                node = tmp;
        }
        list_init(list);
}

ListPtr list_create()
{
        ListPtr list = Malloc(sizeof(List));
        list_init(list);

        return list;
}

void list_dispose(ListPtr list)
{
        list_destroy(list);
        free(list);
}

/* common methods */
enum Status list_insert_after(ListPtr list, NodePtr node, DataType data)
{
        // node must be empty or one of the list node
        // it should be legal
        NodePtr new_node = Malloc(sizeof(ListNode));
        new_node->data = data;
        new_node->next = NULL;

        if (node == NULL) {  // insert at the front
                if (list_size(list) == 0) {  // empty list
                        list->head = new_node;
                        list->tail = new_node;
                } else {
                        new_node->next = list->head;
                        list->head = new_node;
                }
        } else {  // insert at common place
                if (node == list->tail) {  // insert at the last
                        node->next = new_node;
                        list->tail = new_node;
                } else {
                        new_node->next = node->next;
                        node->next = new_node;
                }
        }
        list->size ++;

        return OK;
}

enum Status list_push_back(ListPtr list, DataType data)
{
        list_insert_after(list, list_last_node(list), data);
}

enum Status list_push_front(ListPtr list, DataType data)
{
        list_insert_after(list, NULL, data);
}


enum Status list_remove_after(ListPtr list, NodePtr node)
{
        if (node == NULL) {  // kick the first one
                if (list_size(list) == 0) {
                        return OK;
                }
                if (list_size(list) == 1) {
                        free(list->head);
                        list_init(list);
                        return OK;
                }
                // size >= 2
                NodePtr tmp = list->head;
                list->head = list->head->next;
                list->size --;
                free(tmp);
                return OK;
        } else {  // kick common place but take care, empty, first, last
                if (list_size(list) == 0) {
                        return OK;
                }
                if (list_size(list) == 1) {  // only one
                        free(list->head);
                        list_init(list);
                        return OK;
                } else if (node == list->tail) {  // size >= 2
                        return OK;
                } else if (node->next = list->tail) {  // remove last one
                        free(node->next);
                        node->next = NULL;
                        list->tail = node;
                        list->size --;
                        return OK;
                }
        }
        return OK;
}

enum Status list_pop_front(ListPtr list)
{
        list_remove_after(list, NULL);
}

enum Status list_pop_back(ListPtr list)
{
        // maybe a little slower, but anyway, it's ok
        list_remove_after(list, list_node_previous(list, list_last_node(list)));
}

int list_size(ListPtr list)
{
        return list->size;
}

NodePtr list_at(ListPtr list, int pos)
{
        NodePtr node = list->head;
        int n = 0;
        while (node && ( (n++) == pos)) {
                node = node->next;
                n ++;
        }
        return node;
}

void list_print(ListPtr list)
{
        NodePtr node = list->head;
        while (node) {
                printf("%4d ", node->data);
                node = node->next;
        }
        printf("\n");
}

void list_reverse(ListPtr list)
{
        if (list_size(list) == 0 || list_size(list) == 1) {
                return ;
        }
        NodePtr node = list->head;
        NodePtr p = list->head->next;
        while (p) {
                NodePtr q = p->next;
                p->next = list->head;
                list->head = p;
                p = q;
        }
        node->next = NULL;
}

void list_swap(ListPtr lista, ListPtr listb)
{
        ListPtr tmp = list_create();
        tmp->head = lista->head;
        tmp->tail = lista->tail;
        tmp->size = lista->size;

        listb->head = lista->head;
        listb->tail = lista->tail;
        listb->size = lista->size;

        lista->head = tmp->head;
        lista->tail = tmp->tail;
        lista->size = tmp->size;

        list_dispose(tmp);
        return ;
}

NodePtr list_last_node(ListPtr list)
{
        if (list->head == NULL) return NULL;
        NodePtr node = list->head;
        while (node && node->next) {
                node = node->next;
        }
        return node;
}

NodePtr list_find_key(ListPtr list, DataType data)
{
        NodePtr node = list->head;
        while (node) {
                if (node->data == data) {
                        return node;
                }
        }
        return NULL;
}

enum Status list_remove_current(ListPtr list, NodePtr node)
{
        return list_remove_after(list, list_node_previous(list, node));
}

enum Status list_remove_kth_node(ListPtr list, int pos)
{
        return list_remove_after(list, list_node_previous(list, list_at(list, pos)));
}

NodePtr list_node_previous(ListPtr list, NodePtr node)
{
        if (node == list->head) return NULL;
        NodePtr p = list->head;
        while (p) {
                if (p->next == node) {
                        return p;
                }
        }
        return NULL;
}

NodePtr list_node_next(ListPtr list, NodePtr node)
{
        if (node) {
                return node->next;
        } else {
                return NULL;
        }
}
