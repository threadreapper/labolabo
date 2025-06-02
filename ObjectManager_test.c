#include "ObjectManager.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void *custom_ctor() {
    char *str = (char *)malloc(12);
    strcpy(str, "HelloWorld");
    return str;
}

void custom_dtor(void *obj) {
    free(obj);
}

void test_default_ctor_and_dtor() {
    object_manager_t *obj = create_object(10, NULL, NULL);
    assert(obj != NULL);
    assert(obj->count == 1);

    retain_object(obj);
    assert(obj->count == 2);

    release_object(obj);
    assert(obj->count == 1);

    release_object(obj);
}

void test_custom_ctor_and_dtor() {
    object_manager_t *obj = create_object(0, custom_ctor, custom_dtor);
    assert(obj != NULL);
    assert(obj->count == 1);

    char *str = (char *)obj->object;
    assert(strcmp(str, "HelloWorld") == 0);

    release_object(obj);
}

int main() {
    test_default_ctor_and_dtor();
    test_custom_ctor_and_dtor();
    printf("All tests passed!\n");
    return 0;
}
