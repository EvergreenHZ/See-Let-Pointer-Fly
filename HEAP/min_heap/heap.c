#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "common.h"

#define MINELEMENT (-10000)

MHPtr heap_init(int cap)
{
        MHPtr h = Malloc(sizeof(struct MininumHeap));
        h->size = 0;
        h->capacity = cap;
        h->keys = Malloc(sizeof(int) * (1 + cap));
        h->keys[0] = MINELEMENT;

        return h;
}

void heap_destroy(MHPtr h)
{
        if (h) {
                free(h->keys);
                free(h);
        }
}

bool heap_is_full(MHPtr h)
{
        return h->size == h->capacity ? true : false;
}

bool heap_is_empty(MHPtr h)
{
        return h->size == 0 ? true : false;
}

void heap_insert(MHPtr h, int key)
{
        int i;

        if (heap_is_full(h)) {
                error("heap is full!");
        } else {
                for (i = ++h->size; h->keys[i / 2] > key && i > 1; i /= 2) {
                        h->keys[i] = h->keys[i / 2];  // sift up
                }
                h->keys[i] = key;
        }
}

int heap_delete_min(MHPtr h)
{
        int parent ,child;
        if (heap_is_empty(h)) {
                error("heap is empty!");
        } else {
                int last_key = h->keys[h->size --];
                int min_key = h->keys[1];
                for (parent = 1; parent * 2 <= h->size; parent = child) {
                        child = parent * 2;
                        if (child != h->size && h->keys[child] > h->keys[child + 1]) {
                                child ++;
                        }

                        if (last_key > h->keys[child]) {
                                h->keys[parent] = h->keys[child];
                        } else {
                                break;
                        }
                }
                h->keys[parent] = last_key;
                return min_key;
        }
}

int heap_extra_min(MHPtr h)
{
        if (heap_is_empty(h)) {
                error("heap is empty!");
        } else {
                return h->keys[1];
        }
}

void heap_delete_min2(MHPtr h)
{
        if (heap_is_empty(h)) {
                error("heap is empty!");
        } else {
                int last_key = h->keys[h->size--];
                h->keys[1] = last_key;
                int left_child, right_child;
                for (int i = 1; i * 2 <= h->size; i *= 2) {
                        left_child = i * 2;
                        right_child = left_child + 1;
                        if (right_child < h->size) {
                                if (h->keys[left_child] < h->keys[right_child]) {
                                        swap(h->keys + i, h->keys + left_child);
                                } else {
                                        swap(&h->keys[left_child], &h->keys[i]);
                                }
                        } else {
                                swap(&h->keys[i], &h->keys[left_child]);
                        }
                }
        }
}

void heap_print(MHPtr h)
{
        if (h->size > 0) {
                //printf("heap size: %d ", h->size);
                for (int i = 1; i <= h->size; i++) {
                        printf("%d ", h->keys[i]);
                }
                printf("\n");
        }
}
