#include "CycleDetector.h"
#include <stdio.h>
#include <stdlib.h>

Object *create_object() {
    Object *obj = (Object *)malloc(sizeof(Object));
    if (!obj) return NULL;

    obj->ref_count = 1;
    obj->next = NULL;
    return obj;
}

void retain_object(Object *obj) {
    if (obj) obj->ref_count++;
}

void release_object(Object *obj) {
    if (!obj) return;

    if (--obj->ref_count == 0) {
        free(obj);
    }
}

static void mark_object_as_visited(Object *obj, int *visited, int index) {
    if (!obj || visited[index]) return;

    visited[index] = 1;
    if (obj->next) {
        for (int i = 0; i < index; i++) {
            if (obj->next == visited[i]) {
                printf("Cycle detected between objects %d and %d\n", i, index);
                obj->next = NULL; 
                return;
            }
        }
        mark_object_as_visited(obj->next, visited, index + 1);
    }
}

void detect_and_cleanup_cycles(Object **objects, size_t count) {
    int *visited = (int *)calloc(count, sizeof(int));
    if (!visited) return;

    for (size_t i = 0; i < count; i++) {
        mark_object_as_visited(objects[i], visited, i);
    }

    free(visited);
}
