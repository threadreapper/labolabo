#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "PoolAllocator.h"
#include <stddef.h>
#include <stdint.h>

typedef struct {
    const char *key;
    void *value;
    uint8_t is_deleted;
    uint8_t is_used;
} Item;

typedef struct {
    size_t capacity;
    size_t value_size;
    PoolAllocator *allocator;
    Item *items;
} HashTable;

int hash_table_init(HashTable *table, size_t capacity, PoolAllocator *allocator, size_t value_size);
int hash_table_insert(HashTable *table, const char *key, void *value);
void *hash_table_get(HashTable *table, const char *key);
int hash_table_delete(HashTable *table, const char *key);
void hash_table_free(HashTable *table);

#endif // HASH_TABLE_H
