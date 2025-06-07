#include "dynamic_array.h"
#include "LinearAllocator.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    LinearAllocator *allocator = create_linear_allocator(1024);
    DynamicArray array;
    dynamic_array_init(&array, allocator, 2, sizeof(int));

    int x = 10, y = 20, z = 30;
    dynamic_array_add(&array, &x);
    dynamic_array_add(&array, &y);
    dynamic_array_add(&array, &z);

    assert(array.size == 3);
    assert(*(int *)dynamic_array_get(&array, 0) == 10);

    dynamic_array_del(&array, 1);
    assert(array.size == 2);

    dynamic_array_free(&array);
    destroy_linear_allocator(allocator);

    LinearAllocator *alloc1 = create_linear_allocator(256);
    DynamicArray array1;
    dynamic_array_init(&array1, alloc1, 3, sizeof(int));

    int a = 1, b = 2, c = 3;
    dynamic_array_add(&array1, &a);
    dynamic_array_del(&array1, 0);
    dynamic_array_add(&array1, &b);
    dynamic_array_add(&array1, &c);

    assert(array1.size == 2);
    assert(*(int *)dynamic_array_get(&array1, 0) == 2);
    assert(*(int *)dynamic_array_get(&array1, 1) == 3);
    destroy_linear_allocator(alloc1);

    LinearAllocator *alloc2 = create_linear_allocator(64);
    DynamicArray array2;
    dynamic_array_init(&array2, alloc2, 2, sizeof(int));

    dynamic_array_del(&array2, 100);
    dynamic_array_add(&array2, &a);
    dynamic_array_del(&array2, 1);
    assert(array2.size == 1);
    destroy_linear_allocator(alloc2);

    LinearAllocator *alloc3 = create_linear_allocator(128);
    DynamicArray array3;
    dynamic_array_init(&array3, alloc3, 2, sizeof(int));

    dynamic_array_add(&array3, &a);
    dynamic_array_free(&array3);

    dynamic_array_init(&array3, alloc3, 1, sizeof(int));
    dynamic_array_add(&array3, &b);
    assert(*(int *)dynamic_array_get(&array3, 0) == 2);
    destroy_linear_allocator(alloc3);

    return 0;
}
