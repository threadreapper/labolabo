#include "LinkedListOps.h"
#include <assert.h>
#include <stdio.h>

void test_initialize_list() {
    List list;
    initialize_list(&list);
    assert(list.head == NULL);
    assert(list.count == 0);
}

void test_prepend() {
    List list;
    initialize_list(&list);
    prepend(&list, 42);
    assert(get_count(&list) == 1);
    destroy_list(&list);
}

void test_append() {
    List list;
    initialize_list(&list);

    int result;
    append(&list, 10);
    assert(get_count(&list) == 1);
    assert(!get_value_at(&list, 0, &result) && result == 10);

    append(&list, 20);
    assert(get_count(&list) == 2);
    assert(!get_value_at(&list, 1, &result) && result == 20);

    destroy_list(&list);
}

void test_insert_at() {
    List list;
    initialize_list(&list);

    int result;
    insert_at(&list, 0, 10);
    assert(get_count(&list) == 1);
    assert(!get_value_at(&list, 0, &result) && result == 10);

    insert_at(&list, 1, 20);
    assert(get_count(&list) == 2);
    assert(!get_value_at(&list, 1, &result) && result == 20);

    destroy_list(&list);
}

void test_remove_at() {
    List list;
    initialize_list(&list);

    int result;
    append(&list, 10);
    append(&list, 20);
    append(&list, 30);

    remove_at(&list, 1);
    assert(get_count(&list) == 2);
    assert(!get_value_at(&list, 0, &result) && result == 10);

    remove_at(&list, 0);
    assert(get_count(&list) == 1);
    assert(!get_value_at(&list, 0, &result) && result == 30);

    destroy_list(&list);
}

int main() {
    test_initialize_list();
    test_prepend();
    test_append();
    test_insert_at();
    test_remove_at();

    return 0;
}