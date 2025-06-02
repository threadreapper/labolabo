#ifndef REF_COUNTER_H
#define REF_COUNTER_H

#include <stddef.h>

#include "PoolAllocator.h"

typedef struct {
  size_t count;
  void *object;
} ref_count_t;

int initialize_ref_allocator(PoolAllocator *allocator, size_t block_size,
                             size_t num_blocks);

ref_count_t *create_ref_object(PoolAllocator *allocator, size_t object_size);

void retain_ref(ref_count_t *ref);

void release_ref(PoolAllocator *allocator, ref_count_t *ref);

#endif  // REF_COUNTER_H
