#include "../inc/pathfinder.h"

static void clear_list_of_parent(t_parent **list) {
    t_parent *node = *list;
    t_parent *next = NULL;

    while (node) {
        next = node->next;
        mx_strdel(&node->name);
        free(node);
        node = next;
    }

    *list = NULL;
}

void mx_clear_parents(t_parent **arr, int size) {
    for (int i = 0; i < size; i++) {
        clear_list_of_parent(&arr[i]);
    }
    free(arr);
}
