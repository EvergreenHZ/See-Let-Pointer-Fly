#include "stack.h"

DataType stack_peek(Stack *stack)
{
        if (stack_size(stack) == 0) {
                Error("peek an empty stack");
        }

        return stack->next->data;  // dummy head
}

DataType stack_pop(Stack *stack)
{
        DataType data = stack_peek(stack);
        list_pop_front(stack);

        return data;
}
