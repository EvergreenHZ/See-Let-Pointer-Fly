#pragma once

#include <stdbool.h>

// let's forget weights for a moment

typedef enum {UNDIRECTED=0, DIRECTED} GraphType;

struct AdjListNode {
        int vertex;
        struct AdjListNode* next;
};

struct Graph {
        GraphType type;
        int number_vertices;
        struct AdjListNode** adj_list;
};

typedef struct Graph Graph;
typedef struct Graph* GraphPtr;
typedef struct AdjListNode Node;
typedef struct AdjListNode* NodePtr;

GraphPtr graph_create(int, GraphType);

void graph_destroy(GraphPtr);

void graph_add_edge(GraphPtr, int, int);

//void graph_delete_edge(GraphPtr, int, int);

//void graph_display(GraphPtr);

NodePtr create_node(int);
