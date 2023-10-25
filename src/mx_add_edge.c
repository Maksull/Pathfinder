#include "../inc/pathfinder.h"

// Add an edge to the graph connecting two vertices with the given names, indices, and weight.
void mx_add_edge(t_graph *graph, char *src_name, int src_index, char *dst_name, int dst_index, int weight)
{
    // Add an edge from the source node to the destination node.
    mx_push_back_node(&graph->array[src_index]->list, dst_index, dst_name, weight);
    
    // Add a corresponding edge from the destination node to the source node for an undirected graph.
    mx_push_back_node(&graph->array[dst_index]->list, src_index, src_name, weight);
}
