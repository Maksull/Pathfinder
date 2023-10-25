#include "../inc/pathfinder.h"

// Create a path tree structure for a given source node.
t_source *mx_create_path_tree(int size, char **islands_names, int src_index)
{
    // Allocate memory for the path tree structure.
    t_source *path_tree = (t_source *)malloc(sizeof(t_source));
    
    // Set the size of the path tree and the name of the source node.
    path_tree->size = size;
    path_tree->src_name = mx_strdup(islands_names[src_index]);

    // Allocate memory for the destination nodes and initialize their paths.
    path_tree->dests = (t_destination *)malloc(size * sizeof(*(path_tree->dests)));
    for (int i = 0; i < size; i++)
    {
        // Copy the destination node name.
        path_tree->dests[i].name = mx_strdup(islands_names[i]);
        
        // Initialize the paths for the destination node as NULL.
        path_tree->dests[i].paths = NULL;
    }

    return path_tree;
}
