#include "../inc/pathfinder.h"

// Function to set the path for a given destination.
static void set_path(t_parent *u_node, t_node *current_path, t_source *path_tree, t_parent **parents, int dest_index) {
    int u_index = u_node->prev_vert_index;

    // If the current node has no previous node (source), save the path.
    if (u_index == -1) {
        if (!mx_is_path_saved(path_tree->dests[dest_index].paths, current_path)) {
            mx_push_front_path(&path_tree->dests[dest_index].paths, 0);
            mx_copy_list_of_node(&path_tree->dests[dest_index].paths->list, current_path);
            mx_reset_weight_of_path(&path_tree->dests[dest_index].paths);
        }
        return;
    }

    // Add the current node to the path and recursively explore previous nodes.
    mx_push_front_node(&current_path, u_node->index, u_node->name, u_node->weight);

    t_parent *parent_node = parents[u_index];
    while (parent_node) {
        set_path(parent_node, current_path, path_tree, parents, dest_index);
        parent_node = parent_node->next;
    }

    // Remove the current node from the path.
    mx_pop_front_node(&current_path);
}

// Function to get the size of a list of paths.
static int list_of_paths_size(t_path *list) {
    t_path *node = list;
    int size = 0;

    while (node) {
        node = node->next;
        size++;
    }

    return size;
}

// Function to delete extra paths from the list that are longer than a given weight.
static void del_extra_paths(t_path **list, int weight) {
    t_path *node = (*list)->next;
    t_path *prev = *list;

    if (node == NULL) {
        // If there is only one path in the list, check if its weight exceeds the given weight.
        if (prev->weight > weight) {
            mx_del_path_node(&prev); // Delete the path if it's longer.
        }
        return;
    }

    // Loop through the paths to find and delete those with weights exceeding the given weight.
    while (node->next) {
        if (node->weight > weight) {
            prev->next = node->next;
            mx_del_path_node(&node);
            node = prev->next;
            continue;
        }

        prev = prev->next;
        node = node->next;
    }

    // Check the last path in the list, and delete it if its weight exceeds the given weight.
    if (node->weight > weight) {
        prev->next = NULL;
        mx_del_path_node(&node);
    }

    // Check the first path in the list, and delete it if its weight exceeds the given weight.
    node = *list;
    if (node->weight > weight) {
        (*list) = (*list)->next;
        mx_del_path_node(&node);
    }
}

// Function to process paths for a given destination in the path tree.
static void process_path(t_source *path_tree, t_parent **parents, int index, int weight_of_shortest) {
    t_parent *u = parents[index];
    t_node *current_path = NULL;

    // Generate paths from parent nodes for the current destination.
    while (u) {
        set_path(u, current_path, path_tree, parents, index);
        u = u->next;
    }

    // If there are multiple paths to the destination, remove the extra ones.
    if (list_of_paths_size(path_tree->dests[index].paths) > 1) {
        del_extra_paths(&path_tree->dests[index].paths, weight_of_shortest);
    }

    // Clear the temporary path.
    mx_clear_list_of_nodes(&current_path);
}

// Dijkstra's algorithm implementation.
void mx_dijkstra(t_graph *graph, int src_index, char *src_name, t_source **path_tree) {
    int graph_size = graph->size;

    // Create a priority queue structure for the algorithm.
    t_node_adjacency *pq = (t_node_adjacency *)malloc(sizeof(t_node_adjacency));
    pq->list = NULL;

    // Create an array to hold parent nodes for each vertex.
    t_parent **parents = malloc(graph_size * sizeof(*parents));
    // Initialize an array to hold the shortest path weight for each vertex.
    long path_weight[graph_size];

    for (int i = 0; i < graph_size; i++) {
        path_weight[i] = __INT_MAX__;
        parents[i] = NULL;
    }

    mx_push_back_parent(&parents[src_index], -1, src_index, src_name, 0); // Set the source as the starting point.
    path_weight[src_index] = 0;

    mx_push_back_node(&pq->list, src_index, src_name, 0); // Initialize the priority queue with the source node.

    // Dijkstra's algorithm main loop.
    while (pq->list) {
        int u = pq->list->index;
        mx_pop_front_node(&pq->list); // Remove the node with the smallest known path weight.

        t_node *neighbor_node = graph->array[u]->list; // Renamed variable to 'neighbor_node'.

        while (neighbor_node) {
            int v = neighbor_node->index;

            if (path_weight[u] != __INT_MAX__) {
                // Calculate the potential weight to reach vertex v through vertex u.
                long potential_weight = path_weight[u] + neighbor_node->weight;

                if (potential_weight <= path_weight[v]) {
                    if (potential_weight < path_weight[v]) {
                        path_weight[v] = potential_weight; // Update the shortest path weight.
                        mx_pop_back_parent(&parents[v]); // Remove previous parents.
                    }

                    if (!mx_check_parent_dup(parents[v], u, neighbor_node->index, neighbor_node->name, neighbor_node->weight)) {
                        mx_push_front_parent(&parents[v], u, neighbor_node->index, neighbor_node->name, neighbor_node->weight); // Set a new parent node.
                    }

                    mx_push_back_node(&pq->list, v, neighbor_node->name, path_weight[v]); // Add the vertex to the priority queue.
                }
            }

            neighbor_node = neighbor_node->next;
        }
    }

    // Process and store the paths for each destination in the path tree.
    for (int i = 0; i < graph_size; i++) {
        process_path(*path_tree, parents, i, path_weight[i]);
    }

    // Clean up and free allocated memory.
    mx_clear_parents(parents, graph_size);
    mx_clear_list_of_nodes(&pq->list);
    free(pq);
}
