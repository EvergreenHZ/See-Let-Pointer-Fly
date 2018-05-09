#pragma once

#include <stdbool.h>

#define LCHILD(x) (x * 2)
#define RCHILD(x) (x * 2 + 1)
#define PARENT(x) (x / 2)

//typedef struct Node {
//        int key;
//        void* satellite_data_ptr;
//} Node;

typedef struct MininumHeap {
        int size;
        int capacity;
        int* keys;
} MininumHeap;

typedef struct Node* NodePtr;
typedef struct MininumHeap* MHPtr;

MHPtr heap_init(int cap);

void heap_destroy(MininumHeap *h);

//MHPtr heapify(int keys[], int);

void build_min_heap_from_array(MininumHeap* h, int arr[], int len);

void heap_insert(MininumHeap *h, int data);  // data not good

//void heap_delete(MininumHeap *h);

//NodePtr heap_get_min(MininumHeap* h);

//NodePtr heap_top(MininumHeap*);

int heap_extra_min(MHPtr);

int heap_delete_min(MininumHeap*);

void heap_delete_min2(MHPtr);

bool heap_is_full(MininumHeap*);

bool heap_is_empty(MininumHeap*);

void heap_print(MHPtr);
