#include <stdio.h>
#include "queue.h"
#include "list.h"

int main()
{
        //struct Node list;  // a dummy node
        //list_init(&list);
        struct Node queue;
        queue_init(&queue);

        int num;
        while ( !(num = random_int() % 20)) {
                num = random_int() % 20;
        }

        for (int i = 0; i < num; i++) {
                //printf("%4d\n", i);
                queue_enqueue(&queue, random_int() % 100);
        }

        list_print(&queue);

        for (int i = 0; i < num; i++) {
                queue_dequeue(&queue);
                list_print(&queue);
        }

        queue_dequeue(&queue);

        return 0;
}
