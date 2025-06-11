#include "line_alloc.h"
#include <assert.h>

void line_init_test() { 
  Line_buffer buf;
  size_t test_size = 1024;
  linear_init(&buf, test_size);
  assert(buf.mem != NULL);
  assert(buf.totalSize == test_size);
  assert(buf.offset == 0);
}
void line_alloc_accuracy_test() { 
  Line_buffer buf;
  size_t test_size = 1024;
  size_t ptr_size = 128;
  linear_init(&buf, test_size);
  void *ptr = linear_alloc(&buf, ptr_size);
  assert(ptr != NULL);
  assert(ptr == buf.mem);
  assert(buf.offset == ptr_size);
}
void line_alloc_accuracy_two_elements_test() { 
  Line_buffer buf;
  size_t test_size = 1024;
  size_t ptr1_size = 128;
  size_t ptr2_size = 128;
  linear_init(&buf, test_size);
  void *ptr1 = linear_alloc(&buf, ptr1_size);
  void *ptr2 = linear_alloc(&buf, ptr2_size);
  assert(ptr2 != NULL);
  assert(ptr2 == (char *)ptr1 + ptr2_size);
  assert(buf.offset == ptr2_size + ptr1_size);
}
void line_too_much_memory_test() { 
  Line_buffer buf;
  size_t test_size = 1024;
  size_t too_big = 2048;
  linear_init(&buf, test_size);
  void *ptr_fail = linear_alloc(&buf, too_big);
  assert(ptr_fail == NULL);
  assert(0 == buf.offset);
}
void line_try_to_alloc_zero_test() { 
  Line_buffer buf;
  size_t test_size = 1024;
  linear_init(&buf, test_size);
  void *ptr_zero = linear_alloc(&buf, 0);
  assert(ptr_zero == NULL);
}
void line_reset_test() { 
  Line_buffer buf;
  size_t test_size = 1024;
  linear_init(&buf, test_size);
  size_t ptr_size = 128;
  void *ptr = linear_alloc(&buf, ptr_size);
  assert(ptr == buf.mem);
  linear_reset(&buf);
  assert(buf.mem == NULL);
  assert(buf.offset == 0);
}

int main() {
  line_init_test();
  line_alloc_accuracy_test();
  line_alloc_accuracy_two_elements_test();
  line_too_much_memory_test();
  line_try_to_alloc_zero_test();
  line_reset_test();
  return 0;
}
