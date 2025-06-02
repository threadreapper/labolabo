#include "ObjectManager.h"
#include <stdlib.h>
#include <string.h>

object_manager_t *create_object(size_t object_size, constructor_t ctor, destructor_t dtor) {
    object_manager_t *obj = (object_manager_t *)malloc(sizeof(object_manager_t));
    if (!obj) return NULL;

    if (ctor) {
        obj->object = ctor();
    } else {
        obj->object = malloc(object_size);
    }

    if (!obj->object) {
        free(obj);
        return NULL;
    }

    obj->dtor = dtor;

    obj->count = 1;
    return obj;
}

void retain_object(object_manager_t *obj) {
    if (obj) obj->count++;
}

void release_object(object_manager_t *obj) {
    if (!obj) return;

    if (--obj->count == 0) {
        if (obj->dtor) {
            obj->dtor(obj->object);
        } else {
            free(obj->object);
        }

        free(obj);
    }
}
