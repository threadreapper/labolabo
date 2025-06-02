#include "StackOps.h"

#include <assert.h>
#include <stdio.h>

void run_tests() {
  Stack *stack = create_stack(1);
  assert(stack != NULL);
  assert(is_stack_empty(stack));

  assert(add_to_stack(stack, 42) == 0);
  assert(!is_stack_empty(stack));

  assert(add_to_stack(stack, 99) == STACK_FULL);

  int result;
  assert(remove_from_stack(stack, &result) == 0 && result == 42);
  assert(remove_from_stack(stack, &result) == STACK_EMPTY);

  destroy_stack(stack);
}

int main() {
  run_tests();
  printf("All tests passed successfully!\n");
  return 0;
}
