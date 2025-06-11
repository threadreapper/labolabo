#include "hashtable.h"
#include <string.h>
#include <stdlib.h> 

static unsigned long hash_string(const char* str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

void hashtable_init(HashTable* table, size_t capacity, Allocator* allocator) {
    table->capacity = capacity;
    table->size = 0;
    table->allocator = allocator;
    table->buckets = allocator->alloc(capacity * sizeof(HashTableEntry*));
    memset(table->buckets, 0, capacity * sizeof(HashTableEntry*));
}

void hashtable_insert(HashTable* table, const char* key, void* value) {
    unsigned long hash = hash_string(key);
    size_t index = hash % table->capacity;
    
    HashTableEntry* entry = table->buckets[index];
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            entry->value = value;
            return;
        }
        entry = entry->next;
    }
    
    entry = table->allocator->alloc(sizeof(HashTableEntry));
    entry->key = table->allocator->alloc(strlen(key) + 1);
    strcpy(entry->key, key);
    entry->value = value;
    entry->next = table->buckets[index];
    table->buckets[index] = entry;
    table->size++;
}

void* hashtable_get(HashTable* table, const char* key) {
    unsigned long hash = hash_string(key);
    size_t index = hash % table->capacity;
    
    HashTableEntry* entry = table->buckets[index];
    while (entry) {
        if (strcmp(entry->key, key) == 0)
            return entry->value;
        entry = entry->next;
    }
    return NULL;
}

void hashtable_del(HashTable* table, const char* key) {
    unsigned long hash = hash_string(key);
    size_t index = hash % table->capacity;
    
    HashTableEntry** prev = &table->buckets[index];
    HashTableEntry* entry = table->buckets[index];
    
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            *prev = entry->next;
            table->allocator->free(entry->key);
            table->allocator->free(entry);
            table->size--;
            return;
        }
        prev = &entry->next;
        entry = entry->next;
    }
}

void hashtable_free(HashTable* table) {
    for (size_t i = 0; i < table->capacity; i++) {
        HashTableEntry* entry = table->buckets[i];
        while (entry) {
            HashTableEntry* next = entry->next;
            table->allocator->free(entry->key);
            table->allocator->free(entry);
            entry = next;
        }
    }
    table->allocator->free(table->buckets);
    table->buckets = NULL;
    table->capacity = 0;
    table->size = 0;
}
