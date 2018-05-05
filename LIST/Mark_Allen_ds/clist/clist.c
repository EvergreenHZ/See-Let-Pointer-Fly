#include "clist.h"
#include <stdio.h>
#include <stdlib.h>

void clist_init(Clist clist)
{
        clist->data = 0;
        clist->next = clist;
}

void clist_destroy(Clist clist)
{
        NodePtr node = clist->next;  // clist is not null
        while (node != clist) {
                clist->next = node->next;
                free(node);
                node = clist->next;
        }
}

void clist_print(Clist clist)
{
        NodePtr node = clist->next;
        if (clist_size(clist) == 0) return;

        while (node != clist) {
                printf("%4d ", node->data);
                node = node->next;
        }
        printf("\n");
}

enum Status clist_insert_after(Clist clist, NodePtr node, DataType data)
{
        NodePtr new_node = malloc(sizeof(struct Node));
        if (new_node == NULL) return ERR;

        new_node->data = data;
        new_node->next = NULL;
        if (node == NULL) {
                NodePtr tmp = clist->next;
                new_node->next = clist->next;
                clist->next = new_node;
        } else {  // insert common place
                NodePtr tmp = node->next;
                node->next = new_node;
                new_node->next = tmp;
        }

        return OK;
}

enum Status clist_remove_after(Clist clist, NodePtr node)
{
        if (node == NULL) {  // remove the first node
                if (clist_size(clist) == 0) return OK;
                NodePtr tmp = clist->next;
                clist->next = clist->next->next;
                free(tmp);
        } else {  // remove common place
                if (node->next == clist) return ERR;
                NodePtr tmp = node->next;
                node->next = node->next->next;
                free(tmp);
        }

        return OK;
}

int clist_size(Clist clist)
{
        NodePtr node = clist;
        int n = 0;
        while (node && ((node = node->next) != clist)) {
                n++;
        }
        return n;
}

/**
 * return NULL if empty
 */
NodePtr clist_last_node(Clist clist)
{
        if (clist == NULL) {
                return NULL;
        }
        NodePtr p = clist;
        while (p->next) {
                p = p->next;
        }
        return p;
}

enum Status clist_push_back(Clist clist, DataType data)
{
        NodePtr last_node = clist_last_node(clist);
        return clist_insert_after(clist, last_node, data);
}

NodePtr clist_find_previous(Clist clist, NodePtr current_node)
{
        if (clist == NULL) {
                return NULL;  // it won't be this case
        }
        NodePtr p = clist;
        while (p->next != current_node && p->next != clist) {  // you can't infinity loop
                p = p->next;
        }
        return p;
}

enum Status clist_remove_current(Clist clist, NodePtr current_node)
{
        NodePtr previous = clist_find_previous(clist, current_node);
        return clist_remove_after(clist, previous);
}
