#include "queue.h"
#include "stdio.h"
#include "stdlib.h"

void queue_init(Queue *q, int cap)
{
        q->front = 0;
        q->rear  = -1;
        vector_init(&q->vec, cap);
}

void queue_destroy(Queue *q)
{
        vector_destroy(&q->vec);
        q->front = 0;
        q->rear  = -1;
}

int queue_size(Queue *q)
{
        return q->vec.size;
}

int queue_empty(Queue *q)
{
        return q->vec.size == 0;
}

int queue_full(Queue *q)
{
        return q->vec.size == q->vec.capacity;
}

DataType queue_front(Queue *q)
{
        if (queue_empty(q)) {
                exit(-1);
        } else {
                return q->vec.buffer[q->front];
        }
}

DataType queue_rear(Queue *q)
{
        if (queue_empty(q)) {
                exit(-1);
        } else {
                return q->vec.buffer[q->rear];
        }
}

void queue_enqueue(Queue *q, DataType data)
{
        if (queue_full(q)) {
                return ;
        } else {
                q->rear = (q->rear + 1) % q->vec.capacity;
                q->vec.buffer[q->rear] = data;
                q->vec.size ++;
        }
}

DataType queue_dequeue(Queue *q)
{
        if (queue_empty(q)) {
                printf("queue is empty");
                exit(-1);
        } else {
                DataType value = q->vec.buffer[q->front];
                q->front = (q->front + 1) % q->vec.capacity;
                q->vec.size --;
                return value;
        }
}
