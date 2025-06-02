#include "PoolAllocator.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void run_tests() {
  PoolAllocator allocator;
  const size_t block_size = 32;
  const size_t num_blocks = 8;

  int status = initialize_pool(&allocator, block_size, num_blocks);
  assert(status == 0 && "Initialization failed");

  void *blocks[num_blocks];
  for (size_t i = 0; i < num_blocks; ++i) {
    blocks[i] = allocate_from_pool(&allocator);
    assert(blocks[i] != NULL && "Allocation failed");
  }

  assert(allocate_from_pool(&allocator) == NULL &&
         "Over-allocation should fail");

  free_to_pool(&allocator, blocks[2]);
  void *new_block = allocate_from_pool(&allocator);
  assert(new_block == blocks[2] && "Reuse after free failed");

  for (size_t i = 0; i < num_blocks; ++i) {
    free_to_pool(&allocator, blocks[i]);
  }

  for (size_t i = 0; i < num_blocks; ++i) {
    assert(allocate_from_pool(&allocator) != NULL && "Re-allocation failed");
  }

  free(allocator.memory_start);
  printf("All tests passed successfully!\n");
}

int main() {
  run_tests();
  return 0;
}
