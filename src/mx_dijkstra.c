#include "../inc/pathfinder.h"

static void set_path(t_parent *u_node, t_node *current_path, t_source *path_tree, t_parent **parents, int dest_index) {
    int u_index = u_node->prev_vert_index;

    if (u_index == -1) {
        if (!mx_is_path_saved(path_tree->dests[dest_index].paths, current_path)) {
            mx_push_front_path(&path_tree->dests[dest_index].paths, 0);
            mx_copy_list_of_node(&path_tree->dests[dest_index].paths->list, current_path);
            mx_reset_weight_of_path(&path_tree->dests[dest_index].paths);
        }
        return;
    }
    mx_push_front_node(&current_path, u_node->index, u_node->name, u_node->weight);

    t_parent *parent_node = parents[u_index];
    while (parent_node) {
        set_path(parent_node, current_path, path_tree, parents, dest_index);
        parent_node = parent_node->next;
    }

    mx_pop_front_node(&current_path);
}

static int list_of_paths_size(t_path *list) {
    t_path *node = list;
    int size = 0;

    while (node) {
        node = node->next;
        size++;
    }

    return size;
}

static void del_extra_paths(t_path **list, int weight) {
    t_path *node = (*list)->next;
    t_path *prev = *list;

    if (node == NULL) {
        if (prev->weight > weight) {
            mx_del_path_node(&prev);
        }
        return;
    }

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

    if (node->weight > weight) {
        prev->next = NULL;
        mx_del_path_node(&node);
    }

    node = *list;
    if (node->weight > weight) {
        (*list) = (*list)->next;
        mx_del_path_node(&node);
    }
}

static void process_path(t_source *path_tree, t_parent **parents, int index, int weight_of_shortest) {
    t_parent *u = parents[index];
    t_node *current_path = NULL;

    while (u) {
        set_path(u, current_path, path_tree, parents, index);
        u = u->next;
    }

    if (list_of_paths_size(path_tree->dests[index].paths) > 1) {
        del_extra_paths(&path_tree->dests[index].paths, weight_of_shortest);
    }

    mx_clear_list_of_nodes(&current_path);
}


void mx_dijkstra(t_graph *graph, int src_index, char *src_name, t_source **path_tree) {
    int graph_size = graph->size;

    t_node_adjacency *pq = (t_node_adjacency *)malloc(sizeof(t_node_adjacency));
    pq->list = NULL;

    t_parent **parents = malloc(graph_size * sizeof(*parents));
    long path_weight[graph_size];

    for (int i = 0; i < graph_size; i++) {
        path_weight[i] = __INT_MAX__;
        parents[i] = NULL;
    }

    mx_push_back_parent(&parents[src_index], -1, src_index, src_name, 0);
    path_weight[src_index] = 0;

    mx_push_back_node(&pq->list, src_index, src_name, 0);

    while (pq->list) {
        int u = pq->list->index;
        mx_pop_front_node(&pq->list);

        t_node *adj_vertex = graph->array[u]->list;

        while (adj_vertex) {
            int v = adj_vertex->index;

            if (path_weight[u] != __INT_MAX__) {
                long potential_weight = path_weight[u] + adj_vertex->weight;

                if (potential_weight <= path_weight[v]) {
                    if (potential_weight < path_weight[v]) {
                        path_weight[v] = potential_weight;
                        mx_pop_back_parent(&parents[v]);
                    }

                    if (!mx_check_parent_dup(parents[v], u, adj_vertex->index, adj_vertex->name, adj_vertex->weight)) {
                        mx_push_front_parent(&parents[v], u, adj_vertex->index, adj_vertex->name, adj_vertex->weight);
                    }

                    mx_push_back_node(&pq->list, v, adj_vertex->name, path_weight[v]);
                }
            }

            adj_vertex = adj_vertex->next;
        }
    }

    for (int i = 0; i < graph_size; i++) {
        process_path(*path_tree, parents, i, path_weight[i]);
    }

    mx_clear_parents(parents, graph_size);
    mx_clear_list_of_nodes(&pq->list);
    free(pq);
}
