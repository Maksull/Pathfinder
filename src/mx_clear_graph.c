#include "../inc/pathfinder.h"

// Clear and free the memory of a graph structure, including its vertices and edges.
void mx_clear_graph(t_graph **graph) {
    if (*graph == NULL) {
        return; // Nothing to clear if the graph is already NULL.
    }

    // Traverse the graph's array of vertices.
    for (int i = 0; i < (*graph)->size; i++) {
        if ((*graph)->array[i] != NULL) {
            // Clear and free the linked list of nodes.
            mx_clear_list_of_nodes(&(*graph)->array[i]->list);

            // Free the memory of the current adjacency list.
            free((*graph)->array[i]);
        }
    }

    // Free the memory of the graph's array of adjacency lists.
    free((*graph)->array);

    // Free the memory of the graph structure itself.
    free(*graph);

    // Set the graph pointer to NULL to indicate an empty graph.
    *graph = NULL;
}
