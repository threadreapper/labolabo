#include "StackOps.h"
#include <stdio.h>
#include <stdlib.h>

#define STACK_FULL 1
#define STACK_EMPTY 2

Stack *create_stack(size_t size) {
    Stack *stack = malloc(sizeof(Stack));
    if (!stack) {
        return NULL;
    }
    stack->data = malloc(size * sizeof(int));
    if (!stack->data) {
        free(stack);
        return NULL;
    }
    stack->top = -1;
    stack->size = size;
    return stack;
}

int is_stack_empty(Stack *stack) {
    return stack->top == -1;
}

int add_to_stack(Stack *stack, int value) {
    if (stack->top + 1 == stack->size) {
        return STACK_FULL;
    }
    stack->data[++stack->top] = value;
    return 0;
}

int remove_from_stack(Stack *stack, int *value) {
    if (is_stack_empty(stack)) {
        return STACK_EMPTY;
    }
    *value = stack->data[stack->top--];
    return 0;
}

void destroy_stack(Stack *stack) {
    free(stack->data);
    free(stack);
}
