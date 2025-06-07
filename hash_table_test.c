#include "hash_table.h"
#include "PoolAllocator.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_hash_table() {
    PoolAllocator pool;
    const size_t block_size = sizeof(Node);
    const size_t num_blocks = 10; 
    initialize_pool(&pool, block_size, num_blocks);

    HashTable table;
    hash_table_init(&table, 8, &pool);

    int a = 10, b = 20, c = 30;

    assert(!hash_table_insert(&table, "key1", &a));
    assert(*(int *)hash_table_get(&table, "key1") == 10);

    assert(hash_table_insert(&table, "key1", &b));
    assert(*(int *)hash_table_get(&table, "key1") == 20);

    assert(!hash_table_del(&table, "key1"));
    assert(hash_table_del(&table, "key1"));

    for (size_t i = 0; i < 5; ++i) {
        char key[10];
        sprintf(key, "key%zu", i);
        assert(!hash_table_insert(&table, key, &a));
    }

    int result = hash_table_insert(&table, "overflow", &a);
    if (result == HT_ALLOCATION_FAILED) {
        printf("Expected behavior: Pool memory exhausted.\n");
    } else {
        assert(result == HT_SUCCESS);
    }

    hash_table_free(&table);
    free(pool.memory_start);
}

int main() {
    test_hash_table();
    printf("All tests passed successfully!\n");
    return 0;
}
