#include "../inc/pathfinder.h"

// Create and initialize a new parent node with the given attributes.
t_parent *mx_create_parent(int prev_vert_index, int index, char *name, int weight)
{
    t_parent *new_node = malloc(sizeof(t_parent));
    new_node->prev_vert_index = prev_vert_index;
    new_node->index = index;
    new_node->name = mx_strdup(name);
    new_node->weight = weight;
    new_node->next = NULL;

    return new_node;
}
