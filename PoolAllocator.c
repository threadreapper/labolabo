#include "PoolAllocator.h"
#include <stdint.h>
#include <stdlib.h>

#define ALLOC_FAIL 1
#define INVALID_PTR 2
#define OUT_OF_RANGE 3
#define MISALIGNED_PTR 4

int initialize_pool(PoolAllocator *allocator, size_t block_size, size_t num_blocks) {
    if (block_size < sizeof(void *)) {
        block_size = sizeof(void *);
    }
    allocator->block_size = block_size;
    allocator->num_blocks = num_blocks;
    allocator->memory_start = malloc(block_size * num_blocks);

    if (!allocator->memory_start) {
        return ALLOC_FAIL;
    }

    char *current = (char *)allocator->memory_start;
    for (size_t i = 0; i < num_blocks - 1; ++i) {
        void **next = (void **)(current + block_size);
        *((void **)current) = next;
        current += block_size;
    }
    *((void **)current) = NULL;
    allocator->free_list = allocator->memory_start;
    return 0;
}

void *allocate_from_pool(PoolAllocator *allocator) {
    if (!allocator->free_list) {
        return NULL;
    }

    void *block = allocator->free_list;
    allocator->free_list = *((void **)block);
    return block;
}

int free_to_pool(PoolAllocator *allocator, void *ptr) {
    if (!ptr) {
        return INVALID_PTR;
    }

    char *start = (char *)allocator->memory_start;
    char *end = start + allocator->block_size * allocator->num_blocks;
    char *p = (char *)ptr;

    if (p < start || p >= end) {
        return OUT_OF_RANGE;
    }
    if ((p - start) % allocator->block_size != 0) {
        return MISALIGNED_PTR;
    }

    *((void **)ptr) = allocator->free_list;
    allocator->free_list = ptr;
    return 0;
}
