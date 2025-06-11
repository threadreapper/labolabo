#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hash_function(const char *key, size_t capacity) {
    unsigned int hash = 0;
    while (*key) {
        hash ^= (unsigned char)(*key);
        key++;
    }
    return hash % capacity;
}

int hash_table_init(HashTable *table, size_t capacity, PoolAllocator *allocator, size_t value_size) {
    if (!allocator || capacity == 0) {
        return -1;
    }

    table->capacity = capacity;
    table->value_size = value_size;
    table->allocator = allocator;
    table->items = (Item *)allocator->memory_start;

    for (size_t i = 0; i < capacity; i++) {
        Item *new_item = (Item *)allocate_from_pool(allocator);
        if (!new_item) {
            return -1;
        }
        new_item->key = NULL;
        new_item->value = NULL;
        new_item->is_deleted = 0;
        new_item->is_used = 0;
    }

    return 0;
}

int hash_table_insert(HashTable *table, const char *key, void *value) {
    int index = hash_function(key, table->capacity);

    for (size_t i = index; i < table->capacity + index; i++) {
        int current_index = i % table->capacity;
        Item *item = &table->items[current_index];

        if (!item->is_used) {
            item->value = malloc(table->value_size);
            if (!item->value) {
                return -1;
            }
            memcpy(item->value, value, table->value_size);
            item->key = key;
            item->is_used = 1;
            item->is_deleted = 0;
            return 0;
        }
    }

    return -1;
}

void *hash_table_get(HashTable *table, const char *key) {
    int index = hash_function(key, table->capacity);

    for (size_t i = index; i < table->capacity + index; i++) {
        int current_index = i % table->capacity;
        Item *item = &table->items[current_index];

        if (item->is_used && strcmp(item->key, key) == 0) {
            return item->value;
        }

        if (!item->is_used && !item->is_deleted) {
            return NULL;
        }
    }

    return NULL;
}

int hash_table_delete(HashTable *table, const char *key) {
    int index = hash_function(key, table->capacity);

    for (size_t i = index; i < table->capacity + index; i++) {
        int current_index = i % table->capacity;
        Item *item = &table->items[current_index];

        if (item->is_used && strcmp(item->key, key) == 0) {
            free(item->value);
            item->key = NULL;
            item->value = NULL;
            item->is_deleted = 1;
            item->is_used = 0;
            return 0;
        }

        if (!item->is_used) {
            return -1;
        }
    }

    return -1;
}

void hash_table_free(HashTable *table) {
    free(table->allocator->memory_start);
}
