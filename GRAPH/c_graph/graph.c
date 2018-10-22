#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "graph.h"

GraphPtr graph_create(int number_vertices, GraphType type)
{
        GraphPtr g = Malloc(sizeof(Graph));
        g->number_vertices = number_vertices;
        g->type = type;

        //g->adj_list = Malloc(sizeof(struct AdjListNode) * number_vertices);
        g->adj_list = calloc(number_vertices, sizeof(struct AdjListNode*));

        if (g->adj_list == NULL) {
                error("out of memory!\n");
        }

        return g;
}

void graph_destroy(GraphPtr g)
{
        if (g) {
                for (int i = 0; i < g->number_vertices; i++) {
                        NodePtr p = g->adj_list[i];
                        while (p) {
                                NodePtr q = p->next;
                                free(p);
                                q = p->next;
                        }
                }
        }
}

NodePtr create_node(int vertex)
{
        NodePtr p = Malloc(sizeof(struct AdjListNode));
        p->vertex = vertex;
        p->next = NULL;
        return p;
}

void graph_add_edge(GraphPtr g, int src, int dst)
{
        if (g) {
                NodePtr p = create_node(dst);
                if (g->adj_list[src] == NULL) {
                        g->adj_list[src] = p;
                } else {
                        p->next = g->adj_list[src]->next;
                        g->adj_list[src] = p;
                }
                if (g->type == UNDIRECTED) {
                        NodePtr q = create_node(src);
                        if (g->adj_list[dst] == NULL) {
                                g->adj_list[dst] = q;
                        } else {
                                q->next = g->adj_list[dst]->next;
                                g->adj_list[dst] = q;
                        }
                }
        } else {
                printf("empty graph!\n");
        }
}

//void graph_delete_edge(GraphPtr g, int src, int dst)
//{
//        if (g) {
//                NodePtr p = g->adj_list[src];
//                NodePtr q = p;
//                if (!p) {
//                        return ;
//                } else {
//                        if (p->vertex == dst) {
//                                g->adj_list[src]->next = p->next;
//                                free(q);
//                        } else {

int graph_out_degree(GraphPtr g, int v)
{
        if (g) {
                int n = 0;
                NodePtr p = g->adj_list[v];  // v should be legal
                while (p) {
                        n++;
                        p = p->next;
                }
                return n;
        }
        return -1;
}

int graph_in_degree(GraphPtr g, int v)
{
        if (g) {
                int n = 0;
                for (int i = 0; i < g->number_vertices && i != v; i++) {
                        NodePtr p = g->adj_list[i];
                        while (p) {
                                if (p->vertex == v) {
                                        break;
                                }
                        }
                        if (p) {
                                n++;
                        }
                }
                return n;
        }
        return -1;
}
