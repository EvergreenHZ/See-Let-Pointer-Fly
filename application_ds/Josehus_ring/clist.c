#include "clist.h"
#include <stdio.h>
#include <stdlib.h>

NodePtr clist_init(DataType data)
{
        NodePtr head = clist_create_node(data);
        head->next = head;

        return head;
}

NodePtr clist_create_node(DataType data)
{
        NodePtr node = Malloc(sizeof(struct Node));
        node->data = data;
        node->next = NULL;
}

void clist_destroy(Clist clist)
{
        NodePtr p = clist;
        if (p != NULL) {
                NodePtr q = p->next;
                free(p);
                p = q;
        }
}

NodePtr clist_insert_after(Clist clist, NodePtr current_node, DataType data)
{
        if (clist == NULL) {
                return clist_init(data);
        } 
        NodePtr new_node = clist_create_node(data);
        if (current_node == NULL) {
                new_node->next = clist->next;
                clist->next = new_node;
        } else {  // common place
                new_node->next = current_node->next;
                current_node->next = new_node;
        }
        return new_node;
}

NodePtr clist_push_back(Clist clist, DataType data)
{
        return clist_insert_after(clist, clist_last_node(clist), data);
}

NodePtr clist_last_node(Clist clist)
{
        NodePtr p = clist;
        while (p->next != clist) {
                p = p->next;
        }
        return p;
}

int clist_size(Clist clist)
{
        NodePtr p = clist;
        int n = 1;
        while (p->next != clist) {
                p = p->next;
                n++;
        }

        return n;
}

enum Status clist_remove_after(Clist clist, NodePtr current_node)
{
        if (clist == NULL) {
                return OK;
        }
        if (current_node == NULL) {
                NodePtr p = clist;
                if (p->next = clist) {
                        clist_destroy(clist);
                        return OK;
                } else {
                        NodePtr q = p->next;
                        p->next = q->next;
                        free(q);
                        return OK;
                }
        } else {  // common place
                NodePtr p = current_node->next;
                current_node->next = p->next;
                free(p);
                return OK;
        }
}

NodePtr clist_node_previous(Clist clist, NodePtr current_node)
{
        if (clist == NULL) {
                return NULL;
        }
        NodePtr p = clist;
        while (p->next != current_node) {
                p = p->next;
        }
        return p;
}

enum Status clist_remove_current(Clist clist, NodePtr current_node)
{
        return clist_remove_after(clist, clist_node_previous(clist, current_node));
}
