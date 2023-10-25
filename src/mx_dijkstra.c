#include "../inc/pathfinder.h"

// Set the path for a destination node in the path tree.
static void build_path_to_destination(t_parent *parents[], t_source *path_tree, int dest_index) {
    int stack_size = 100;
    t_parent **stack = (t_parent **)malloc(sizeof(t_parent *) * stack_size);
    int top = -1;

    t_node *current_path = NULL;

    stack[++top] = parents[dest_index];

    // Traverse the parent nodes to construct the path.
    while (top >= 0) {
        t_parent *u_node = stack[top--];
        int u_index = u_node->prev_vert_index;

        // If u_index is -1, it's the source node, so save the constructed path.
        if (u_index == -1) {
            if (!mx_is_path_saved(path_tree->dests[dest_index].paths, current_path)) {
                mx_push_front_path(&path_tree->dests[dest_index].paths, 0);
                mx_copy_list_of_node(&path_tree->dests[dest_index].paths->list, current_path);
                mx_reset_weight_of_path(&path_tree->dests[dest_index].paths);
            }
        } else {
            mx_push_front_node(&current_path, u_node->index, u_node->name, u_node->weight);
            stack[++top] = parents[u_index];

            // Resize the stack if necessary.
            if (top == stack_size - 1) {
                stack_size *= 2;
                stack = (t_parent **)realloc(stack, sizeof(t_parent *) * stack_size);
            }
        }
    }

    mx_clear_list_of_nodes(&current_path);

    free(stack);
}

// Helper function to create a new priority queue.
static t_priority_queue create_priority_queue(int capacity) {
    t_priority_queue queue;
    queue.size = 0;
    queue.capacity = capacity;
    queue.indices = (int *)malloc(sizeof(int) * capacity);
    queue.weights = (int *)malloc(sizeof(int) * capacity);
    return queue;
}

// Helper function to swap two priority queue nodes.
static void swap_priority_queue_nodes(t_priority_queue *queue, int a, int b) {
    int tempIndex = queue->indices[a];
    int tempWeight = queue->weights[a];

    queue->indices[a] = queue->indices[b];
    queue->weights[a] = queue->weights[b];

    queue->indices[b] = tempIndex;
    queue->weights[b] = tempWeight;
}

// Helper function to heapify the priority queue.
static void heapify_priority_queue(t_priority_queue *queue, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < queue->size && queue->weights[left] < queue->weights[smallest])
        smallest = left;

    if (right < queue->size && queue->weights[right] < queue->weights[smallest])
        smallest = right;

    if (smallest != idx) {
        swap_priority_queue_nodes(queue, idx, smallest);
        heapify_priority_queue(queue, smallest);
    }
}

void mx_dijkstra(t_graph *graph, int src_index, char *src_name, t_source **path_tree) {
    int graph_size = graph->size;

    t_priority_queue queue = create_priority_queue(graph_size);
    int *dist = (int *)malloc(graph_size * sizeof(int));
    t_parent **parents = (t_parent **)malloc(graph_size * sizeof(t_parent *));

    for (int i = 0; i < graph_size; i++) {
        dist[i] = __INT_MAX__;
        parents[i] = NULL;
    }

    dist[src_index] = 0;
    mx_push_back_parent(&parents[src_index], -1, src_index, src_name, 0);

    // Push the source node to the priority queue.
    queue.indices[0] = src_index;
    queue.weights[0] = 0;
    queue.size = 1;

    while (queue.size > 0) {
        int u = queue.indices[0];
        // Extract the node with the smallest weight from the priority queue.
        queue.size--;
        if (queue.size > 0) {
            queue.indices[0] = queue.indices[queue.size];
            queue.weights[0] = queue.weights[queue.size];
            heapify_priority_queue(&queue, 0);
        }

        t_node *adj_vertex = graph->array[u]->list;

        while (adj_vertex != NULL) {
            int v = adj_vertex->index;
            int weight = adj_vertex->weight;

            if (dist[u] != __INT_MAX__ && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                mx_pop_back_parent(&parents[v]);

                if (!mx_check_parent_dup(parents[v], u, v, adj_vertex->name, weight)) {
                    mx_push_front_parent(&parents[v], u, v, adj_vertex->name, weight);
                }

                // Add v to the priority queue if not already in it.
                bool v_in_priority_queue = false;
                for (int i = 0; i < queue.size; i++) {
                    if (queue.indices[i] == v) {
                        v_in_priority_queue = true;
                        break;
                    }
                }

                if (!v_in_priority_queue) {
                    queue.indices[queue.size] = v;
                    queue.weights[queue.size] = dist[v];
                    queue.size++;
                }
            }
            adj_vertex = adj_vertex->next;
        }
    }

    for (int i = 0; i < graph_size; i++) {
        build_path_to_destination(parents, *path_tree, i);
    }

    free(dist);
    free(parents);
}
