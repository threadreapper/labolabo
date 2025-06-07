#include "LinearAllocator.h"
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#define ALIGNMENT 8

static size_t align_forward(size_t size) {
    return (size + ALIGNMENT - 1) & ~(ALIGNMENT - 1);
}

LinearAllocator *create_linear_allocator(size_t size) {
    LinearAllocator *allocator = malloc(sizeof(LinearAllocator));
    if (!allocator)
        return NULL;

    allocator->start = malloc(size);
    if (!allocator->start) {
        free(allocator);
        return NULL;
    }

    allocator->used = 0;
    allocator->size = size;
    return allocator;
}

void destroy_linear_allocator(LinearAllocator *allocator) {
    if (allocator) {
        free(allocator->start);
        free(allocator);
    }
}

void *allocate_from_linear_allocator(LinearAllocator *allocator, size_t size) {
    if (!allocator || size == 0)
        return NULL;

    size_t aligned_size = align_forward(size);
    if (allocator->used + aligned_size > allocator->size) {
        return NULL;
    }

    void *ptr = (char *)allocator->start + allocator->used;
    allocator->used += aligned_size;
    return ptr;
}

void reset_linear_allocator(LinearAllocator *allocator) {
    if (allocator) {
        allocator->used = 0;
    }
}
