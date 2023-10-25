#include "../inc/pathfinder.h"

// Recalculate the weight of a path by summing the weights of its vertices.
void mx_reset_weight_of_path(t_path **path)
{
    t_node *node = (*path)->list;
    int new_weight = 0;

    // Iterate through the vertices in the path and accumulate their weights.
    while (node != NULL)
    {
        new_weight += node->weight;
        node = node->next;
    }

    (*path)->weight = new_weight; // Update the weight of the path.
}
