#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* create a list head, a dummy node */
void list_init(List list)
{
        list->next = NULL;
}

void list_destroy(List list)
{
        NodePtr node = list->next;
        while (node) {
                NodePtr tmp = node->next;
                free(node);
                node = tmp;
        }
        list->next = NULL;
}

enum Status list_insert_after(List list, NodePtr node, DataType data)
{
        NodePtr new_node = (NodePtr)malloc(sizeof(NodePtr));
        if (!new_node) {
                printf("malloc failed!\n");
                return ERR;
        }

        new_node->data = data;
        new_node->next = NULL;

        if (!node) {  // insert at the head of the list
                new_node->data = data;
                new_node->next = list->next;
                list->next = new_node;
        } else {
                new_node->next = node->next;
                node->next = new_node;
        }

        return OK;
}

NodePtr list_last_node(List list)
{
        NodePtr node = list->next;
        while (node && node->next) {
                node = node->next;
        }
        return node;  //if node is NULL, empty list
}
// O(n)
enum Status list_push_back(List list, DataType data)
{
        NodePtr node = list_last_node(list);
        return list_insert_after(list, node, data);
}

enum Status list_push_front(List list, DataType data)
{
        NodePtr new_node = (NodePtr)malloc(sizeof(NodePtr));
        if (!new_node) {
                printf("malloc failed!\n");
                return ERR;
        }
        new_node->data = data;
        new_node->next = list->next;
        list->next = new_node;

        return OK;
}

NodePtr list_node_previous(List list, NodePtr node)
{
        if (node == list) return NULL;
        else if (node == NULL) return NULL;
        else {
                NodePtr p = list;
                while (p && p->next != node) {
                        p = p->next;
                }
                return p;
        }
}

NodePtr list_node_next(NodePtr node)
{
        if (node) return node->next;
        return NULL;
}

enum Status list_remove_after(List list, NodePtr node)
{
        if (node == NULL) {  // remove at the head of the list
                if (list->next) {
                        NodePtr tmp = list->next->next;
                        free(list->next);
                        list->next = tmp;
                }
                return OK;
        } else {  // remove somewhere in the list
                NodePtr tmp = NULL;
                if (node->next) tmp = node->next->next;
                free(node->next);
                node->next = tmp;
                return OK;
        }
        return ERR;
}

int list_size(List list)
{
        int n = 0;
        NodePtr node = list;
        while ((node = node->next) != NULL) {
                n++;
        }
        return n;
}

enum Status list_pop_front(List list)
{
        return list_remove_after(list, NULL);
}

enum Status list_pop_back(List list)
{
        NodePtr node = list;
        if (list_size(list) == 0) {
                return OK;
        } else {
                while (node->next && node->next->next) {
                        node = node->next;
                }
                free(node->next);
                node->next = NULL;
                return OK;
        }
        return ERR;
}

NodePtr list_find_key(List list, DataType key)
{
        NodePtr node = list->next;
        while (node && node->data != key) {
                node = node->next;
        }
        return node;
}

NodePtr list_at(List list, int pos)
{
        int n = 1;
        NodePtr node = list->next;
        while (node && n++ != pos) {
                node = node->next;
        }
        return node;
}

void list_print(List list)
{
        NodePtr node = list->next;
        while (node) {
                printf("%4d ", node->data);
                node = node->next;
        }
        printf("\n");
}

enum Status list_remove_current(List list, NodePtr node)
{
        return list_remove_after(list, list_node_previous(list, node));
}

enum Status list_remove_kth_node(List list, int k)
{
        return list_remove_current(list, list_at(list, k));
}
