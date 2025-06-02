#include "RefCounter.h"
#include <assert.h>
#include <stdio.h>

void test_create_and_release() {
    PoolAllocator allocator;
    assert(initialize_ref_allocator(&allocator, sizeof(ref_count_t), 10) == 0);

    ref_count_t *ref = create_ref_object(&allocator, 10);
    assert(ref != NULL);
    assert(ref->count == 1);

    release_ref(&allocator, ref);
}

void test_retain_and_release() {
    PoolAllocator allocator;
    assert(initialize_ref_allocator(&allocator, sizeof(ref_count_t), 10) == 0);

    ref_count_t *ref = create_ref_object(&allocator, 10);
    assert(ref != NULL);

    retain_ref(ref);
    assert(ref->count == 2);

    release_ref(&allocator, ref);
    assert(ref->count == 1);

    release_ref(&allocator, ref);
}

int main() {
    test_create_and_release();
    test_retain_and_release();
    printf("All tests passed!\n");
    return 0;
}
