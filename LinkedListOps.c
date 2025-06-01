#include "LinkedListOps.h"
#include <stdio.h>
#include <stdlib.h>

#define INDEX_ERROR 1
#define MEMORY_ERROR 2

void initialize_list(List *list) {
    list->head = NULL;
    list->count = 0;
}

int prepend(List *list, int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) return MEMORY_ERROR;

    new_node->value = value;
    new_node->next = list->head;
    list->head = new_node;
    list->count++;
    return 0;
}

int append(List *list, int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) return MEMORY_ERROR;

    new_node->value = value;
    new_node->next = NULL;

    if (!list->head) {
        list->head = new_node;
    } else {
        Node *current = list->head;
        while (current->next) current = current->next;
        current->next = new_node;
    }
    list->count++;
    return 0;
}

int insert_at(List *list, int index, int value) {
    if (index < 0 || index > list->count) return INDEX_ERROR;

    if (index == 0) {
        prepend(list, value);
    } else if (index == list->count) {
        append(list, value);
    } else {
        Node *prev = list->head;
        for (int i = 0; i < index - 1; i++) prev = prev->next;

        Node *new_node = (Node *)malloc(sizeof(Node));
        if (!new_node) return MEMORY_ERROR;

        new_node->value = value;
        new_node->next = prev->next;
        prev->next = new_node;
        list->count++;
    }
    return 0;
}

int remove_at(List *list, int index) {
    if (index < 0 || index >= list->count) return INDEX_ERROR;

    Node *to_remove;
    if (index == 0) {
        to_remove = list->head;
        list->head = list->head->next;
    } else {
        Node *prev = list->head;
        for (int i = 0; i < index - 1; i++) prev = prev->next;
        to_remove = prev->next;
        prev->next = to_remove->next;
    }
    free(to_remove);
    list->count--;
    return 0;
}

int get_value_at(List *list, int index, int *result) {
    if (index < 0 || index >= list->count) return INDEX_ERROR;

    Node *current = list->head;
    for (int i = 0; i < index; i++) current = current->next;
    *result = current->value;
    return 0;
}

int get_count(List *list) {
    return list->count;
}

void destroy_list(List *list) {
    Node *current = list->head;
    while (current) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
    list->count = 0;
}