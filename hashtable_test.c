#include "hashtable.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h> 

static void* test_alloc(size_t size) { return malloc(size); }
static void test_free(void* ptr) { free(ptr); }

static Allocator test_allocator = {
    .alloc = test_alloc,
    .free = test_free
};

void test_hashtable_basic() {
    HashTable table;
    hashtable_init(&table, 16, &test_allocator);
    
    int value1 = 42;
    int value2 = 100;
    
    hashtable_insert(&table, "key1", &value1);
    hashtable_insert(&table, "key2", &value2);
    
    assert(hashtable_get(&table, "key1") == &value1);
    assert(hashtable_get(&table, "key2") == &value2);
    assert(hashtable_get(&table, "nonexistent") == NULL);
    
    hashtable_del(&table, "key1");
    assert(hashtable_get(&table, "key1") == NULL);
    assert(hashtable_get(&table, "key2") == &value2);
    
    hashtable_free(&table);
    printf("test_hashtable_basic passed\n");
}

int main() {
    test_hashtable_basic();
    return 0;
}
