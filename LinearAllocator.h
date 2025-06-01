#ifndef LINEAR_ALLOCATOR_H
#define LINEAR_ALLOCATOR_H

#include <stddef.h>

typedef struct {
    void *start;
    size_t used;
    size_t size;
} LinearAllocator;

LinearAllocator *create_linear_allocator(size_t size);
void destroy_linear_allocator(LinearAllocator *allocator);
void *allocate_from_linear_allocator(LinearAllocator *allocator, size_t size);
void reset_linear_allocator(LinearAllocator *allocator);

#endif
