#ifndef POOL_ALLOCATOR_H
#define POOL_ALLOCATOR_H

#include <stddef.h>

typedef struct PoolAllocator {
  size_t block_size;
  size_t num_blocks;
  void *memory_start;
  void *free_list;
} PoolAllocator;

int initialize_pool(PoolAllocator *allocator, size_t block_size,
                    size_t num_blocks);
void *allocate_from_pool(PoolAllocator *allocator);
int free_to_pool(PoolAllocator *allocator, void *ptr);

#endif  // POOL_ALLOCATOR_H
