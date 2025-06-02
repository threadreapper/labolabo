#include "RefCounter.h"
#include <stdlib.h>

int initialize_ref_allocator(PoolAllocator *allocator, size_t block_size,
                             size_t num_blocks) {
    return initialize_pool(allocator, block_size, num_blocks);
}

ref_count_t *create_ref_object(PoolAllocator *allocator, size_t object_size) {
    ref_count_t *ref = (ref_count_t *)allocate_from_pool(allocator);
    if (!ref) return NULL;

    ref->object = malloc(object_size);
    if (!ref->object) {
        free_to_pool(allocator, ref);
        return NULL;
    }

    ref->count = 1; 
    return ref;
}

void retain_ref(ref_count_t *ref) {
    if (ref) ref->count++;
}

void release_ref(PoolAllocator *allocator, ref_count_t *ref) {
    if (!ref || !allocator) return;

    if (--ref->count == 0) {
        free(ref->object);       
        free_to_pool(allocator, ref); 
    }
}
