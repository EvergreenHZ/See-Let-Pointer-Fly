#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

int main()
{
        // 2, 4, 10, 13, 18, 19, 21, 27, 29, 56
        int keys[] = { 29, 10, 2, 4, 18, 27, 13, 56, 19, 21, };
        MHPtr h = heap_init(10);
        for (int i = 0; i < 10; i++) {
                heap_insert(h, keys[i]);
        }
        //heap_print(h);

        int flag = 0;
        for (int i = 0; i < 10; i++) {
                if (flag) {
                        heap_delete_min(h);
                        heap_print(h);
                        flag = 0;
                } else {
                        heap_delete_min2(h);
                        heap_print(h);
                        flag = 1;
                }
        }
        return 0;
}
