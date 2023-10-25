#include "../inc/pathfinder.h"

// Free memory associated with a path node and its vertices.
void mx_del_path_node(t_path **node)
{
    mx_clear_list_of_nodes(&(*node)->list);
    free((*node));
}
