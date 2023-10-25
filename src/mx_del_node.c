#include "../inc/pathfinder.h"

// Free memory associated with a node.
void mx_del_node(t_node **node)
{
    mx_strdel(&(*node)->name);
    free((*node));
}
