#include "../inc/pathfinder.h"

// Create and initialize a new graph with the given number of vertices.
t_graph *mx_create_graph(int V)
{
    t_graph *graph = (t_graph *)malloc(sizeof(t_graph));
    graph->size = V;

    graph->array = (t_node_adjacency **)malloc(V * sizeof(t_node_adjacency));

    for (int i = 0; i < V; ++i)
    {
        graph->array[i] = malloc(sizeof(*(graph->array[i])));
        graph->array[i]->list = NULL;
    }

    return graph;
}
