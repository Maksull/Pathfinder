#include "../inc/pathfinder.h"

// Clear the memory associated with a path tree structure.
void mx_clear_path_tree(t_source **path_tree)
{
    // Loop through all destination nodes in the path tree.
    for (int i = 0; i < (*path_tree)->size; i++)
    {
        // Clear the list of paths for the current destination node.
        mx_clear_list_of_paths(&(*path_tree)->dests[i].paths);
        
        // Free the memory allocated for the name of the destination node.
        mx_strdel(&(*path_tree)->dests[i].name);
    }

    // Free the memory allocated for the name of the source node.
    mx_strdel(&(*path_tree)->src_name);

    // Free the memory allocated for the array of destination nodes and the path tree structure itself.
    free((*path_tree)->dests);
    free((*path_tree));
}
