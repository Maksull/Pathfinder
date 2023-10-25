#include "../inc/pathfinder.h"

// Add a new path node with the specified weight to the beginning of the path list.
void mx_push_front_path(t_path **list, int weight)
{
    t_path *new_node = mx_create_path(weight);

    new_node->next = *list;

    *list = new_node;
}
