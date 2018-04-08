#include "clist.h"
#include <stdio.h>
#include <stdlib.h>

void clist_init(Clist clist)
{
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
