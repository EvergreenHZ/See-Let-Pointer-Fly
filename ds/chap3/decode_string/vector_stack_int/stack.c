#include "stack.h"


DataType stack_int_pop(StackInt *stack) {
  DataType data = stack_int_peek(stack);
  vector_pop_back(stack);

  return data;
}
