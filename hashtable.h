#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stddef.h>
#include <stdlib.h> 

typedef struct Allocator {
    void* (*alloc)(size_t size); 
    void (*free)(void* ptr);
} Allocator;

typedef struct HashTableEntry {
    char* key;
    void* value;
    struct HashTableEntry* next;
} HashTableEntry;

typedef struct HashTable {
    size_t capacity;
    size_t size;
    HashTableEntry** buckets;
    Allocator* allocator;
} HashTable;

void hashtable_init(HashTable* table, size_t capacity, Allocator* allocator);
void hashtable_insert(HashTable* table, const char* key, void* value);
void* hashtable_get(HashTable* table, const char* key);
void hashtable_del(HashTable* table, const char* key);
void hashtable_free(HashTable* table);

#endif 
