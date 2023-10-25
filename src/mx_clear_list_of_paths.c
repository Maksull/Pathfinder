#include "../inc/pathfinder.h"

// Recursively clear and free the memory of a linked list of path nodes.
void mx_clear_list_of_paths(t_path **list)
{
    t_path *node = *list;
    t_path *next = NULL;

    // Traverse the list to clear and free the memory of each path node.
    while (node != NULL)
    {
        // Get a pointer to the next node.
        next = node->next;

        // Clear and free the memory of the current path node.
        mx_del_path_node(&node);

        // Move to the next node.
        node = next;
    }

    // Set the head of the list to NULL to indicate an empty list.
    *list = NULL;
}
