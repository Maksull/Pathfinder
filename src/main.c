#include "../inc/pathfinder.h"

int main(int argc, char const *argv[])
{
    // Check if the correct number of command-line arguments is provided
    if (argc != 2)
    {
        mx_error_wrong_usage();
    }

    // Get the filename from the command-line arguments
    char const *filename = argv[1];

    // Read the contents of the file into a string
    char *str_file = mx_file_to_str(filename);

    // Check if the file does not exist
    if (str_file == NULL)
    {
        mx_error_file_not_exist(filename);
    }

    // Check if the file is empty
    if (mx_strlen(str_file) == 0)
    {
        mx_error_file_empty(filename);
    }

    // Initialize a graph data structure
    t_graph *graph = NULL;

    // Parse the file to create the graph and get island names
    char **islands_names = mx_parse_file(str_file, &graph);

    // Perform pathfinding and output the results
    mx_pathfinder(graph, islands_names);

    // Free dynamically allocated memory
    mx_strdel(&str_file);
    mx_del_strarr(&islands_names);
    mx_clear_graph(&graph);

    return 0;
}
