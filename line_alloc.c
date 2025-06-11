#include "line_alloc.h"

void *linear_alloc(Line_buffer *buf, size_t size) {
  if (!buf || !size) {
    return NULL;
  }
  int newOffset = size + buf->offset;
  if ((int)newOffset > (int)buf->totalSize) {
    return NULL;
  }
  void *ptr = (char *)buf->mem + buf->offset;
  buf->offset = newOffset;
  return ptr;
}

void linear_reset(Line_buffer *buf) {
  free(buf->mem);
  buf->mem = NULL;
  buf->offset = 0;
}

void linear_init(Line_buffer *buf, size_t size) {
  buf->mem = malloc(size);
  buf->totalSize = size;
  buf->offset = 0;
}
