#include "../inc/pathfinder.h"

// Create and initialize a new node with the given attributes.
t_node *mx_create_node_in_graph(int index, char *name, int weight)
{
    t_node *new_node = malloc(sizeof(t_node));
    new_node->index = index;
    new_node->name = mx_strdup(name);
    new_node->weight = weight;
    new_node->next = NULL;

    return new_node;
}
