#pragma once

#include "vector.h"

struct Queue {
        int front;
        int rear;
        struct Vector vector;
};

void queue_init(Queue *);

void queue_destroy(Queue *);

int queue_size(Queue *);

bool queue_empty(Queue *);

DataType queue_front(Queue *);

DataType queue_rear(Queue *);

void queue_enqueue(Queue *q, DataType data);

DataType queue_dequeue(Queue *);
