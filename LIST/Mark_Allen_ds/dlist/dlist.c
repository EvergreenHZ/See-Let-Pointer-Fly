#include <stdio.h>
#include <stdlib.h>
#include "dlist.h"

void dlist_init(DList dlist)
{
        dlist->next = dlist;
        dlist->prev = dlist;
}

void dlist_print(DList dlist)
{
        NodePtr node = dlist->next;
        while (node != dlist) {
                printf("%4d ", node->data);
                node = node->next;
        }
        printf("\n");
}

int dlist_size(DList dlist)
{
        NodePtr node = dlist->next;
        int n = 0;
        while (node != dlist) {
                n++;
                node = node->next;
        }
        return n;
}

void dlist_destroy(DList dlist)
{
        // dlist cann't be NULL, for sure
        NodePtr node = dlist->next;
        while (dlist_size(dlist) != 0) {
                dlist_pop_front(dlist);
        }
        dlist->next = dlist;
        dlist->prev = dlist;
}

void dlist_reverse_print(DList dlist)
{
        NodePtr node = dlist->prev;
        while (node != dlist) {
                printf("%4d ", node->data);
                node = node->prev;
        }
        printf("\n");
}

enum Status dlist_insert_after(DList dlist, NodePtr node, DataType data)
{
        NodePtr new_node = (NodePtr)Malloc(sizeof(struct Node));
        new_node->data = data;
        new_node->prev = NULL;
        new_node->next = NULL;

        if (node == NULL) {  // insert at the front of the list
                dlist->next->prev = new_node;
                new_node->next = dlist->next;
                new_node->prev = dlist;
                dlist->next    = new_node;
        } else {  // insert common place, list size >= 1
                new_node->next = node->next;
                node->next->prev = new_node;
                new_node->prev = node;
                node->next = new_node;
        }

        return OK;
}

NodePtr dlist_last_node(DList dlist)
{
        if (dlist_size(dlist) == 0) return NULL;
        NodePtr node = dlist->next;
        while (node->next != dlist) {
                node = node->next;
        }
        return node;
}

enum Status dlist_push_back(DList dlist, DataType data)
{
        dlist_insert_after(dlist, dlist_last_node(dlist), data);
}

enum Status dlist_push_front(DList dlist, DataType data)
{
        dlist_insert_after(dlist, NULL, data);
}

enum Status dlist_remove_after(DList dlist, NodePtr node)
{
        if (dlist_size(dlist) == 0) {
                Error("remove a empty list");
        }
        //printf("size of list: %4d\n", dlist_size(dlist));
        // size of dlist >= 1
        if (dlist_size(dlist) == 1) {
                NodePtr tmp = dlist->next;
                dlist->next = dlist->next->next;
                dlist->next->next->prev = dlist;
                free(tmp);  // this can never be wrong
        }

        if (node == NULL || node == dlist || node->next == dlist) {  // remove first one
                NodePtr tmp = dlist->next;
                dlist->next = dlist->next->next;
                dlist->next->prev = dlist;
                free(tmp);
                //dlist_print(dlist);
        } else {
                NodePtr tmp = node->next;
                node->next = node->next->next;
                node->next->prev = node;
                free(tmp);
                //dlist_print(dlist);
        }
        return OK;
}

enum Status dlist_pop_front(DList dlist)
{
        return dlist_remove_after(dlist, NULL);
}

enum Status dlist_pop_back(DList dlist)
{
        NodePtr last_node = dlist_last_node(dlist);
        if (last_node == NULL) {
                Error("remove an empty list");
        }
        return  dlist_remove_after(dlist, last_node->prev);
}

enum Status dlist_remove_current(DList dlist, NodePtr node)
{
        node = node ? node->prev : node;
        return dlist_remove_after(dlist, node);
}

NodePtr dlist_node_previous(DList dlist, NodePtr node)
{
        return node ? node->prev : dlist;
}

NodePtr dlist_node_next(DList dlist, NodePtr node)
{
        return node ? node->next : dlist;
}

NodePtr dlist_find_key(DList dlist, DataType data)
{
        NodePtr node = dlist->next;
        while (node != dlist) {
                if (node->data == data) {
                        return node;
                }
                node = node->next;
        }

        return NULL;
}

NodePtr dlist_at(DList dlist, int n)
{
        // the dummy head node named 0th node
        if (n < 0) {
                Error("invalid position\n");
        }
        n %= (dlist_size(dlist) + 1);
        NodePtr iter = dlist;
        int index = 0;
        while (index != n) {
                index++;
                iter = iter->next;
        }
        return iter;
}

NodePtr dlist_create()
{
        NodePtr dummy_head = Malloc(sizeof(struct Node));
        return dummy_head;
}

enum Status dlist_dispose(DList dlist)
{
        dlist_destroy(dlist);
        free(dlist);
}
