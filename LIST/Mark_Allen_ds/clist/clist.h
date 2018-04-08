#include "common.h"

typedef int DataType;

struct Node {
        DataType data;
        struct Node *next;
};

typedef struct Node* Clist;
typedef struct Node* NodePtr;

void clist_init(Clist);

void clist_destroy(Clist);

void clist_print(Clist);

enum Status clist_insert_after(Clist, NodePtr, DataType);

//enum Status clist_push_front(Clist, DataType);

//enum Status clist_push_back(Clist, DataType);

enum Status clist_remove_after(Clist, NodePtr);

//enum Status clist_pop_front(Clist);

//enum Status clist_pop_back(Clist);

//enum Status clist_remove_current(Clist, NodePtr);

//NodePtr clist_node_next(NodePtr);

//NodePtr clist_node_previous(Clist, NodePtr);

//NodePtr clist_last_node(Clist);

NodePtr clist_at(Clist, int);

int clist_size(Clist);
