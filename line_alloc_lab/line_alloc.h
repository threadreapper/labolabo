#include <stdlib.h>

typedef struct Line_buffer_t {
  void *mem;
  size_t totalSize;
  size_t offset;
} Line_buffer;

void *linear_alloc(Line_buffer *buf, size_t size);
void linear_reset(Line_buffer *buf);
void linear_init(Line_buffer *buf, size_t size);
