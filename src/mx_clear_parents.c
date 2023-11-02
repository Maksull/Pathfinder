#include "../inc/pathfinder.h"

// Function to clear and deallocate memory for a list of parent nodes.
static void clear_list_of_parent(t_parent **list) {
    t_parent *node = *list;
    t_parent *next = NULL;

    while (node) {
        next = node->next; // Store the next node to prevent losing the reference.
        mx_strdel(&node->name);
        free(node);
        node = next; // Move to the next node in the list.
    }

    *list = NULL; // Set the list pointer to NULL to indicate an empty list.
}

// Function to clear and deallocate memory for an array of lists of parent nodes.
void mx_clear_parents(t_parent **arr, int size) {
    for (int i = 0; i < size; i++) {
        clear_list_of_parent(&arr[i]); // Clear each list of parent nodes in the array.
    }
    free(arr);
}
