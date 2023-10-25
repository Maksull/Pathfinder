#include "../inc/pathfinder.h"

// Calculate and return the size of a list of vertices.
int mx_list_of_node_size(t_node *list)
{
    t_node *node = list;
    int size = 0;

    while (node != NULL)
    {
        node = node->next;
        size++;
    }

    return size;
}
