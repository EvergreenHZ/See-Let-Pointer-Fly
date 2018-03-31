#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int main()
{
        struct vector a, b, c;

        vector_new(&a, 10);
        vector_new(&b, 10);
        vector_new(&c, 20);

        for (int i = 0; i < 10; i++) {
                vector_push_back(&a, i);
                vector_push_back(&b, 3 * i + 1);
                if (i < 10) vector_push_back(&c, 2 * i);
        }

        vector_reverse(&a);
        vector_print(&a);

        //vector_swap(&a, &c);
        //vector_print(&a);
        //vector_print(&c);

        int index = -11;
        printf("index at %d: %d\n", index, at(&a, index));
        //printf("%d %d %d", at(&b, 100), at(&b, -11), at(&b, -1));

        return 0;
}
