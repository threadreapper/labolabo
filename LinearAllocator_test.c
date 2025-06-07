#include "LinearAllocator.h"
#include <assert.h>
#include <stdio.h>

#define ALIGNMENT 8

int main() {
    LinearAllocator *allocator = create_linear_allocator(1024);
    assert(allocator != NULL);
    assert(allocator->size == 1024);

    int *number = allocate_from_linear_allocator(allocator, sizeof(int));
    *number = 42;
    assert(*number == 42);

    void *large_block = allocate_from_linear_allocator(allocator, 1024);
    assert(large_block == NULL);

    reset_linear_allocator(allocator);
    char *string = allocate_from_linear_allocator(allocator, 100);
    assert(string != NULL);

    size_t previous_used = allocator->used;
    void *aligned_ptr = allocate_from_linear_allocator(allocator, 3);
    assert((size_t)aligned_ptr % ALIGNMENT == 0);
    assert(allocator->used - previous_used == ALIGNMENT);

    destroy_linear_allocator(allocator);
    printf("All tests passed successfully!\n");
    return 0;
}
