#pragma once

#include "vector.h"

typedef struct Queue {
        int front;
        int rear;
        struct Vector vec;
} Queue;

void queue_init(Queue *, int);

void queue_destroy(Queue *);

int queue_size(Queue *);

int queue_empty(Queue *);

int queue_full(Queue *);

DataType queue_front(Queue *);

DataType queue_rear(Queue *);

void queue_enqueue(Queue *q, DataType data);

DataType queue_dequeue(Queue *);
