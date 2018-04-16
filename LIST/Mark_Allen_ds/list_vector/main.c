#include "vector.h"
#include "stdio.h"

int main()
{
        Vector vec;
        vector_init(&vec);

        for (int i = 0; i < 10; i++) {
                vector_push_back(&vec, i);
        }
        vector_print(&vec);

        printf("size of vector: %4d\n", vector_size(&vec));

        for (int i = 0; i < 10; i ++) {
                vector_pop_front(&vec);
                vector_print(&vec);
        }

        // yeah, the last one is empty
        // I mean, it works fine

        return 0;
}
