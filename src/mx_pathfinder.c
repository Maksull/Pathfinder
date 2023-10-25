#include "../inc/pathfinder.h"

// The main pathfinding function to find and print all shortest paths.
void mx_pathfinder(t_graph *graph, char **islands_names)
{
    // Loop through all source nodes in the graph.
    for (int i = 0; i < graph->size; i++)
    {
        // Create a path tree for the current source node.
        t_source *path_tree = mx_create_path_tree(graph->size, islands_names, i);

        // Use Dijkstra's algorithm to find the shortest paths.
        mx_dijkstra(graph, i, islands_names[i], &path_tree);

        // Sort the paths in the path tree by destination node.
        mx_sort_path_tree(path_tree);

        // Print the shortest paths for the current source node.
        mx_print_paths(path_tree, i);

        mx_clear_path_tree(&path_tree);
    }
}
