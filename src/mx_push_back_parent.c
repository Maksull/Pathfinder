#include "../inc/pathfinder.h"

// Add a new parent node to the end of a linked list of parent nodes.
void mx_push_back_parent(t_parent **list, int prev_vert_index, int index, char *name, int weight)
{
    // Create a new parent node.
    t_parent *new_node = mx_create_parent(prev_vert_index, index, name, weight);

    // Find the last node in the linked list.
    t_parent *last_node = *list;

    // If the list is empty, make the new node the head of the list.
    if (*list == NULL)
    {
        *list = new_node;
        return;
    }

    // Traverse the list to find the last node.
    while (last_node->next != NULL)
    {
        last_node = last_node->next;
    }

    // Add the new node to the end of the list.
    last_node->next = new_node;
}
