#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "PoolAllocator.h"
#include <stddef.h>

typedef struct Node Node;
struct Node {
    const char *key;
    void *value;
    struct Node *next;
};

typedef struct HashTable HashTable;
struct HashTable {
    size_t capacity;
    struct Node **buckets;
    PoolAllocator *allocator;
};

#define HT_SUCCESS 0
#define HT_INIT_FAILED -1
#define HT_KEY_EXISTS -2
#define HT_KEY_NOT_FOUND -3
#define HT_ALLOCATION_FAILED -4

int hash_table_init(HashTable *table, size_t capacity, PoolAllocator *allocator);
int hash_table_insert(HashTable *table, const char *key, void *value);
void *hash_table_get(HashTable *table, const char *key);
int hash_table_del(HashTable *table, const char *key);
void hash_table_free(HashTable *table);

#endif // HASH_TABLE_H
