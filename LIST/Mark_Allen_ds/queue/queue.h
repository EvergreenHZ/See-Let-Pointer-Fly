#include "common.h"
#include "list.h"

typedef struct Node* Queue;

#define queue_init list_init

#define queue_destroy list_destroy

#define queue_size list_size

#define queue_empty(queue) (list_size(queue) == 0)

#define queue_front(queue) ((queue)->next)

#define queue_rear(queue) list_last_node(queue)

//#define queue_enqueue(queue, data) list_push_back(queue, data)
enum Status queue_enqueue(Queue, DataType data);

DataType queue_dequeue(Queue );
