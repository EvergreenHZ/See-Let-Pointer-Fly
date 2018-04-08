#include "stack.h"


ElementType stack_int_pop(StackInt *stack) {
  ElementType data = stack_int_peek(stack);
  vector_pop_back(stack);

  return data;
}
