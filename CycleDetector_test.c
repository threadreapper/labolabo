#include "CycleDetector.h"
#include <assert.h>
#include <stdio.h>

void test_cycle_detection() {
    Object *obj1 = create_object();
    Object *obj2 = create_object();

    obj1->next = obj2;
    obj2->next = obj1;

    Object *objects[] = {obj1, obj2};
    detect_and_cleanup_cycles(objects, 2);

    release_object(obj1);
    release_object(obj2);
}

int main() {
    test_cycle_detection();
    printf("All tests passed!\n");
    return 0;
}
