#include "../libmx/inc/libmx.h"

// Data Structures

// Represents a single node in the graph.
typedef struct s_node {
    int index;       // The index of the node.
    char *name;      // The name of the island.
    int weight;      // The weight or distance of the island.
    struct s_node *next;  // Pointer to the next node in the list.
} t_node;

// Represents a list of nodes (vertices) adjacent to a specific island.
typedef struct s_node_adjacency {
    t_node *list;  // List of adjacent nodes.
} t_node_adjacency;

// Represents the main graph structure.
typedef struct s_graph {
    int size;               // The number of islands in the graph.
    t_node_adjacency **array;  // An array of adjacency lists for all islands.
} t_graph;

// Represents a path from one island to another.
typedef struct s_path {
    int weight;          // The total weight or distance of the path.
    t_node *list;        // List of islands in the path.
    struct s_path *next; // Pointer to the next path.
} t_path;

// Represents a destination island with its paths.
typedef struct s_destination {
    char *name;      // The name of the destination island.
    t_path *paths;   // List of paths to other islands.
} t_destination;

// Represents a source island with its destinations.
typedef struct s_source {
    char *src_name;  // The name of the source island.
    int size;        // The number of destinations.
    t_destination *dests;  // List of destination islands.
} t_source;

// Represents a parent node in the path tree.
typedef struct s_parent {
    int prev_vert_index;  // Index of the previous island in the path.
    int index;            // Index of the current island.
    char *name;           // Name of the current island.
    int weight;           // Weight or distance from the source to this island.
    struct s_parent *next;  // Pointer to the next parent node.
} t_parent;

// Define a structure for the priority queue.
typedef struct s_priority_queue {
    int *indices; // Array to store vertex indices.
    int *weights; // Array to store weights.
    int size;
    int capacity;
} t_priority_queue;

// Define a structure to hold parsed bridge information
typedef struct s_parsed_bridge {
    char *island1;
    char *island2;
    int bridge_len;
} t_parsed_bridge;

// Function Declarations

// Error Handling
void mx_printerror(const char *s);
void mx_error_wrong_usage();
void mx_error_file_not_exist(const char *filename);
void mx_error_file_empty(const char *filename);
void mx_error_line_not_valid(int index);
void mx_error_invalid_num_of_islands();
void mx_error_duplicate_bridges();
void mx_error_sum_of_bridges_len_is_too_big();

// Pathfinding
void mx_pathfinder(t_graph *graph, char **islands_names);

// Graph Creation and Manipulation
t_graph *mx_create_graph(int V);
void mx_add_edge(t_graph *graph, char *src_name, int src_index, char *dst_name, int dst_index, int weight);

// Graph Cleanup
void mx_clear_graph(t_graph **graph);

// Node Operations
t_node *mx_create_node_in_graph(int index, char *name, int weight);
void mx_push_back_node(t_node **list, int index, char *name, int weight);
void mx_clear_list_of_nodes(t_node **list);
void mx_del_node(t_node **node);
int mx_list_of_node_size(t_node *list);
void mx_copy_list_of_node(t_node **dest, t_node *src);
void mx_push_front_node(t_node **list, int index, char *name, int weight);

// Dijkstra's Algorithm
t_source *mx_create_path_tree(int size, char **islands_names, int src_index);
void mx_dijkstra(t_graph *graph, int src_index, char *src_name, t_source **path_tree);
t_parent *mx_create_parent(int prev_vert_index, int index, char *name, int weight);

// Path Operations
t_path *mx_create_path(int weight);
t_path *mx_sort_paths_list(t_path *list);
void mx_reset_weight_of_path(t_path **path);
bool mx_is_path_saved(t_path *paths, t_node *new_path);
void mx_push_front_path(t_path **list, int weight);
void mx_clear_list_of_paths(t_path **list);
void mx_del_path_node(t_path **node);

// File Parsing
char **mx_parse_file(char *src, t_graph **graph);

// Utility Functions
bool mx_isdigit(int c);
int mx_atoi(const char *str);

// Path Tree Handling
void mx_sort_path_tree(t_source *path_tree);
void mx_print_paths(t_source *path_tree, int src);
void mx_clear_path_tree(t_source **path_tree);

// Parent Operations
void mx_push_back_parent(t_parent **list, int prev_vert_index, int index, char *name, int weight);
void mx_push_front_parent(t_parent **list, int prev_vert_index, int index, char *name, int weight);
void mx_pop_back_parent(t_parent **head);
bool mx_check_parent_dup(t_parent *list, int prev_vert_index, int index, char *name, int weight);
