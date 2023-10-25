#include "../inc/pathfinder.h"

// Free the memory of a single node, including its name.
static void mx_clear_node(t_node *node) {
    // Deallocate the memory used by the node's name.
    mx_strdel(&node->name);

    // Free the memory of the node itself.
    free(node);
}

// Recursively clear and free the memory of a linked list of nodes.
void mx_clear_list_of_nodes(t_node **list) {
    // Get a pointer to the head of the list.
    t_node *node = *list;

    // Traverse the list to clear and free the memory of each node.
    while (node != NULL) {
        // Get a pointer to the next node.
        t_node *next = node->next;

        // Clear and free the memory of the current node.
        mx_clear_node(node);

        // Move to the next node.
        node = next;
    }

    // Set the head of the list to NULL to indicate an empty list.
    *list = NULL;
}
