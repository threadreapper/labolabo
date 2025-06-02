#ifndef CYCLE_DETECTOR_H
#define CYCLE_DETECTOR_H

#include <stddef.h>
#include <stdlib.h>

typedef struct Object {
  size_t ref_count;
  struct Object *next;
} Object;

Object *create_object();

void retain_object(Object *obj);

void release_object(Object *obj);

void detect_and_cleanup_cycles(Object **objects, size_t count);

#endif  // CYCLE_DETECTOR_H
