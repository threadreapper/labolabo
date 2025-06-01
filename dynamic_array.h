#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include "LinearAllocator.h"
#include <stddef.h>

typedef struct {
    void **data;
    size_t size;
    size_t capacity;
    LinearAllocator *allocator;
    size_t element_size;
} DynamicArray;

void dynamic_array_init(DynamicArray *array, LinearAllocator *allocator,
                        size_t initial_capacity, size_t element_size);
void dynamic_array_add(DynamicArray *array, const void *element);
void *dynamic_array_get(const DynamicArray *array, size_t index);
void dynamic_array_del(DynamicArray *array, size_t index);
void dynamic_array_free(DynamicArray *array);

#endif
