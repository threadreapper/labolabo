#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <stddef.h>
#include <stdlib.h>

typedef void *(*constructor_t)(void);
typedef void (*destructor_t)(void *);

typedef struct {
    size_t count;        
    void *object;        
    destructor_t dtor;   
} object_manager_t;

object_manager_t *create_object(size_t object_size, constructor_t ctor, destructor_t dtor);

void retain_object(object_manager_t *obj);

void release_object(object_manager_t *obj);

#endif // OBJECT_MANAGER_H
