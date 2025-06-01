#include "dynamic_array.h"
#include "LinearAllocator.h"
#include <string.h>

void dynamic_array_init(DynamicArray *array, LinearAllocator *allocator,
                        size_t initial_capacity, size_t element_size) {
    array->data = initial_capacity > 0
                      ? (void **)allocate_from_linear_allocator(
                            allocator, initial_capacity * sizeof(void *))
                      : NULL;
    array->size = 0;
    array->capacity = initial_capacity;
    array->allocator = allocator;
    array->element_size = element_size;
}

void dynamic_array_add(DynamicArray *array, const void *element) {
    if (array->size >= array->capacity) {
        size_t new_capacity = array->capacity == 0 ? 1 : array->capacity * 2;
        void **new_data = (void **)allocate_from_linear_allocator(
            array->allocator, new_capacity * sizeof(void *));
        if (array->data) {
            memcpy(new_data, array->data, array->size * sizeof(void *));
        }
        array->data = new_data;
        array->capacity = new_capacity;
    }
    void *element_copy =
        allocate_from_linear_allocator(array->allocator, array->element_size);
    memcpy(element_copy, element, array->element_size);
    array->data[array->size++] = element_copy;
}

void *dynamic_array_get(const DynamicArray *array, size_t index) {
    return (index < array->size) ? array->data[index] : NULL;
}

void dynamic_array_del(DynamicArray *array, size_t index) {
    if (index >= array->size)
        return;
    memmove(&array->data[index], &array->data[index + 1],
            (array->size - index - 1) * sizeof(void *));
    array->size--;
}

void dynamic_array_free(DynamicArray *array) {
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
}
