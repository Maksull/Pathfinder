#include "../inc/pathfinder.h"

// Add a new node with the specified index, name, and weight to the beginning of the node list.
void mx_push_front_node(t_node **list, int index, char *name, int weight)
{
    t_node *new_node = mx_create_node_in_graph(index, name, weight);

    new_node->next = *list;

    *list = new_node;
}
