#include "queue.h"

DataType queue_dequeue(Queue q)
{
        if (list_size(q) == 0) {
                Error("try to dequeue an empty queue\n");
        }

        DataType data = q->next->data;
        list_pop_front(q);

        return data;
}

enum Status queue_enqueue(Queue q, DataType data)
{
        return list_push_back(q, data);
}
