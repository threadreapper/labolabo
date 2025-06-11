#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HT_SUCCESS 0
#define HT_INIT_FAILED -1
#define HT_KEY_EXISTS -2
#define HT_KEY_NOT_FOUND -3
#define HT_ALLOCATION_FAILED -4

static size_t hash(const char *key, size_t capacity) {
    size_t hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % capacity;
}

int hash_table_init(HashTable *table, size_t capacity, PoolAllocator *allocator) {
    table->capacity = capacity;
    table->allocator = allocator;
    table->buckets = (struct Node **)calloc(capacity, sizeof(struct Node *));
    return table->buckets ? HT_SUCCESS : HT_INIT_FAILED;
}

int hash_table_insert(HashTable *table, const char *key, void *value) {
    size_t index = hash(key, table->capacity);
    struct Node *current = table->buckets[index];

    while (current) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            return HT_KEY_EXISTS;
        }
        current = current->next;
    }

    struct Node *newNode = (struct Node *)allocate_from_pool(table->allocator);
    if (!newNode) {
        return HT_ALLOCATION_FAILED;
    }

    size_t key_length = strlen(key) + 1;
    newNode->key = allocate_from_pool(table->allocator);
    if (!newNode->key) {
        free_to_pool(table->allocator, newNode);
        return HT_ALLOCATION_FAILED;
    }

    memcpy(newNode->key, key, key_length);

    newNode->value = value;
    newNode->next = table->buckets[index];
    table->buckets[index] = newNode;

    return HT_SUCCESS;
}

void *hash_table_get(HashTable *table, const char *key) {
    size_t index = hash(key, table->capacity);
    struct Node *current = table->buckets[index];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

int hash_table_del(HashTable *table, const char *key) {
    size_t index = hash(key, table->capacity);
    struct Node *prev = NULL;
    struct Node *current = table->buckets[index];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                table->buckets[index] = current->next;
            }
            free_to_pool(table->allocator, current);
            return HT_SUCCESS;
        }
        prev = current;
        current = current->next;
    }
    return HT_KEY_NOT_FOUND;
}

void hash_table_free(HashTable *table) {
    for (size_t i = 0; i < table->capacity; ++i) {
        struct Node *current = table->buckets[i];
        while (current) {
            struct Node *next = current->next;
            if (current->key) {
                free_to_pool(table->allocator, (void *)current->key);
            }
            free_to_pool(table->allocator, current);
            current = next;
        }
    }
    free(table->buckets);
    table->buckets = NULL;
}
