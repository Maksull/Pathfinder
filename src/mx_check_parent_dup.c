#include "../inc/pathfinder.h"

// Check for duplicate parent nodes in a linked list.
bool mx_check_parent_dup(t_parent *list, int prev_vert_index, int index, char *name, int weight)
{
    t_parent *node = list;

    // Traverse the linked list to check for duplicates.
    while (node != NULL)
    {
        // Compare the attributes of the current node with the given values.
        if (node->index == index && !mx_strcmp(node->name, name) && node->weight == weight && node->prev_vert_index == prev_vert_index)
        {
            return true; // Found a duplicate.
        }

        node = node->next;
    }

    return false; // No duplicates found.
}
