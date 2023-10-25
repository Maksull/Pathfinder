#include "../inc/pathfinder.h"

// Sort the paths within the path tree for each destination node.
void mx_sort_path_tree(t_source *path_tree)
{
    for (int i = 0; i < path_tree->size; i++)
    {
        // Sort the list of paths for the current destination node.
        mx_sort_paths_list(path_tree->dests[i].paths);
    }
}
