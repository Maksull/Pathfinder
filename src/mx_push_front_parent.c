#include "../inc/pathfinder.h"

// Add a new parent node to the front of a linked list of parent nodes.
void mx_push_front_parent(t_parent **list, int prev_vert_index, int index, char *name, int weight)
{
    // Create a new parent node.
    t_parent *new_node = mx_create_parent(prev_vert_index, index, name, weight);

    // Set the new node to point to the current head of the list.
    new_node->next = *list;

    // Update the head of the list to the new node.
    *list = new_node;
}
