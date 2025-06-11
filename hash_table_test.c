	#include "hash_table.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_hash_table_init() {
    HashTable table;
    size_t capacity = 8;
    PoolAllocator allocator;
    initialize_pool(&allocator, sizeof(Item), capacity);

    assert(hash_table_init(&table, capacity, &allocator, sizeof(const char *)) == 0);
    assert(table.capacity == capacity);
    hash_table_free(&table);
}

void test_hash_table_insert() {
    HashTable table;
    size_t capacity = 8;
    PoolAllocator allocator;
    initialize_pool(&allocator, sizeof(Item), capacity);

    hash_table_init(&table, capacity, &allocator, sizeof(const char *));
    assert(hash_table_insert(&table, "44608", "Harry") == 0);
    assert(hash_table_insert(&table, "11392", "Peter") == 0);
    assert(hash_table_insert(&table, "16745", "Mike") == 0);
    assert(hash_table_insert(&table, "10897", "Tayler") == 0);
    hash_table_free(&table);
}

void test_hash_table_get() {
    HashTable table;
    size_t capacity = 8;
    PoolAllocator allocator;
    initialize_pool(&allocator, sizeof(Item), capacity);

    hash_table_init(&table, capacity, &allocator, sizeof(const char *));
    hash_table_insert(&table, "44698", "Harry");
    hash_table_insert(&table, "11092", "Peter");
    hash_table_insert(&table, "16745", "Mike");
    hash_table_insert(&table, "10897", "Tayler");

    assert(strcmp((char *)hash_table_get(&table, "44698"), "Harry") == 0);
    assert(strcmp((char *)hash_table_get(&table, "11092"), "Peter") == 0);
    assert(strcmp((char *)hash_table_get(&table, "16745"), "Mike") == 0);
    assert(strcmp((char *)hash_table_get(&table, "10897"), "Tayler") == 0);
    hash_table_free(&table);
}

void test_hash_table_delete() {
    HashTable table;
    size_t capacity = 8;
    PoolAllocator allocator;
    initialize_pool(&allocator, sizeof(Item), capacity);

    hash_table_init(&table, capacity, &allocator, sizeof(const char *));
    hash_table_insert(&table, "44698", "Harry");
    hash_table_insert(&table, "11092", "Peter");
    hash_table_insert(&table, "16745", "Mike");
    hash_table_insert(&table, "10897", "Tayler");

    assert(strcmp((char *)hash_table_get(&table, "16745"), "Mike") == 0);
    assert(hash_table_delete(&table, "16745") == 0);
    assert(hash_table_get(&table, "16745") == NULL);
    hash_table_free(&table);
}

int main() {
    test_hash_table_init();
    test_hash_table_insert();
    test_hash_table_get();
    test_hash_table_delete();
    printf("All tests passed successfully!\n");
    return 0;
}
