#include "../inc/pathfinder.h"

// Helper function to print a boundary line.
static void print_boundary() {
    for (size_t i = 0; i < 40; i++) {
        mx_printchar('=');
    }
    mx_printchar('\n');
}

// Print the shortest paths from a source node to all other destination nodes.
void mx_print_paths(t_source *path_tree, int src) {
    // Loop through all destination nodes.
    for (int i = src + 1; i < path_tree->size; i++) {
        t_path *paths = path_tree->dests[i].paths;

        // Loop through all paths to the current destination node.
        while (paths != NULL) {
            print_boundary();

            // Print the source and destination node names.
            mx_printstr("Path: ");
            mx_printstr(path_tree->src_name);
            mx_printstr(" -> ");
            mx_printstr(path_tree->dests[i].name);
            mx_printstr("\n");

            mx_printstr("Route: ");
            mx_printstr(path_tree->src_name);
            mx_printstr(" -> ");

            t_node *vert = paths->list;
            while (vert != NULL) {
                mx_printstr(vert->name);
                if (vert->next != NULL) {
                    mx_printstr(" -> ");
                }
                vert = vert->next;
            }
            mx_printstr("\n");

            // Print the distance of the path.
            mx_printstr("Distance: ");
            vert = paths->list;
            if (vert->next != NULL) {
                while (vert != NULL) {
                    mx_printint(vert->weight);

                    if (vert->next != NULL) {
                        mx_printstr(" + ");
                    }
                    vert = vert->next;
                }
                mx_printstr(" = ");
            }
            mx_printint(paths->weight);

            mx_printstr("\n");

            print_boundary();

            paths = paths->next;
        }
    }
}
