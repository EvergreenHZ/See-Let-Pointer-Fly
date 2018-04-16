#include <stdio.h>
#include "stack.h"

int main()
{
        Stack stack;  // create a stack, dummy head; but I don't care

        stack_init(&stack);

        for (int i = 0; i < 10; i ++) {
                stack_push(&stack, i);
        }

        printf("size: %4d \n", stack_size(&stack));
        list_print(&stack);
        printf("size: %4d \n", stack_size(&stack));

        //for (int i = 0; i < stack_size(&stack); i++) {
        for (int i = 0; i < 10; i++) {
                printf("%4d ", stack_pop(&stack));
        }
        printf("\n");
        printf("size: %4d \n", stack_size(&stack));
        list_print(&stack);

        stack_pop(&stack);
        stack_destroy(&stack);

        return 0;
}
