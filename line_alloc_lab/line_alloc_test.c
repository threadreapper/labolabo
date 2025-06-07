#include "line_alloc.h"
#include <assert.h>

void line_test1() { // На правильность работы инициализации
  Line_buffer buf;
  size_t test_size = 1024;
  linear_init(&buf, test_size);
  assert(buf.mem != NULL);
  assert(buf.totalSize == test_size);
  assert(buf.offset == 0);
}
void line_test2() { // На правильность работы аллокатора
  Line_buffer buf;
  size_t test_size = 1024;
  size_t ptr_size = 128;
  linear_init(&buf, test_size);
  void *ptr = linear_alloc(&buf, ptr_size);
  assert(ptr != NULL);
  assert(ptr == buf.mem);
  assert(buf.offset == ptr_size);
}
void line_test3() { // На правильность работы аллокатора на два элемента
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
void line_test4() { // Работа при попытки выделения слишком большого количества
                    // памяти
  Line_buffer buf;
  size_t test_size = 1024;
  size_t too_big = 2048;
  linear_init(&buf, test_size);
  void *ptr_fail = linear_alloc(&buf, too_big);
  assert(ptr_fail == NULL);
  assert(0 == buf.offset);
}
void line_test5() { // Попытка выделить 0 байт
  Line_buffer buf;
  size_t test_size = 1024;
  linear_init(&buf, test_size);
  void *ptr_zero = linear_alloc(&buf, 0);
  assert(ptr_zero == NULL);
}
void line_test6() { // сброс аллокатора
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
  line_test1();
  line_test2();
  line_test3();
  line_test4();
  line_test5();
  line_test6();
  return 0;
}
