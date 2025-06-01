#ifndef LINKED_LIST_OPS_H
#define LINKED_LIST_OPS_H

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int count;
} List;

void initialize_list(List *list);
int prepend(List *list, int value);
int append(List *list, int value);
int insert_at(List *list, int index, int value);
int remove_at(List *list, int index);
int get_value_at(List *list, int index, int *result);
int get_count(List *list);
void destroy_list(List *list);

#endif // LINKED_LIST_OPS_H