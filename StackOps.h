#ifndef STACK_OPS_H
#define STACK_OPS_H

#include <stddef.h>

// Константы для статусов операций
#define STACK_FULL  1
#define STACK_EMPTY 2

typedef struct {
    int *data;
    int top;
    size_t size;
} Stack;

Stack *create_stack(size_t size);
int is_stack_empty(Stack *stack);
int add_to_stack(Stack *stack, int value);
int remove_from_stack(Stack *stack, int *value);
void destroy_stack(Stack *stack);

#endif // STACK_OPS_H
