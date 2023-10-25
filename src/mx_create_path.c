#include "../inc/pathfinder.h"

// Create and initialize a new path node with the given weight.
t_path *mx_create_path(int weight)
{
    t_path *new_node = malloc(sizeof(t_path));
    new_node->weight = weight;
    new_node->list = NULL;
    new_node->next = NULL;

    return new_node;
}
