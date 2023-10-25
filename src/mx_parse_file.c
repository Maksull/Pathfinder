#include "../inc/pathfinder.h"

// Count the number of bridges in the input data.
static int count_bridges(char **lines)
{
    int i = 0;
    while (lines[i + 1] != NULL)
    {
        i++;
    }
    return i;
}

// Check if a given string is a valid number.
static bool is_number_valid(char *str)
{
    size_t i = 0;
    while (str[i] != '\0')
    {
        if (!mx_isdigit(str[i]))
        {
            return false;
        }
        i++;
    }

    return i > 0;
}

// Check if a character is an alphabet letter.
static bool isalpha(int c)
{
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
    {
        return true;
    }
    return false;
}

// Check if a string is a valid name (contains only alphabet letters).
static bool is_name_valid(char *str, int length)
{
    for (int i = 0; i < length; i++)
    {
        if (!isalpha((unsigned char)str[i]))
        {
            return false;
        }
    }
    return length > 0;
}

// Check if a new island name is unique.
static bool is_new_island(char **islands, int num_of_islands, int islands_counter, char *island)
{
    for (int i = 0; i < islands_counter && i < num_of_islands; i++)
    {
        if (!mx_strcmp(islands[i], island))
        {
            return false;
        }
    }
    return true;
}

// Check and add a new island to the list of islands.
static void check_new_island(char **islands, int num_of_islands, int *islands_counter, char *island)
{
    if (is_new_island(islands, num_of_islands, *islands_counter, island))
    {
        if (*islands_counter < num_of_islands)
        {
            islands[*islands_counter] = mx_strdup(island);
        }
        (*islands_counter)++;
    }
}

// Find the index of an island in the list of islands.
static int find_index(char **islands, char *island)
{
    for (int i = 0; islands[i] != NULL; i++)
    {
        if (!mx_strcmp(island, islands[i]))
        {
            return i;
        }
    }
    return -1;
}

// Parse a line of the input and validate it, returning the parsed bridge information.
static t_parsed_bridge parse_bridge(char *line, int line_index) {
    t_parsed_bridge parsed;
    char *island1, *island2;
    int bridge_len;
    
    if (mx_count_substr(line, "-") != 1 || mx_count_substr(line, ",") != 1) {
        mx_error_line_not_valid(line_index);
    }

    island1 = mx_strndup(line, mx_get_char_index(line, '-'));
    line += mx_get_char_index(line, '-') + 1;

    island2 = mx_strndup(line, mx_get_char_index(line, ','));
    line += mx_get_char_index(line, ',') + 1;

    if (!is_name_valid(island1, mx_strlen(island1)) || !is_name_valid(island2, mx_strlen(island2)) || !is_number_valid(line)) {
        mx_error_line_not_valid(line_index);
    }

    bridge_len = mx_atoi(line);
    
    if (bridge_len <= 0) {
        mx_error_line_not_valid(line_index);
    }

    if (!mx_strcmp(island1, island2)) {
        mx_error_line_not_valid(line_index);
    }

    parsed.island1 = island1;
    parsed.island2 = island2;
    parsed.bridge_len = bridge_len;

    return parsed;
}

// Check if a bridge is a duplicate.
static bool is_duplicate_bridge(t_parsed_bridge *parsed_bridges, int size, t_parsed_bridge bridge) {
    for (int i = 0; i < size; i++) {
        if (parsed_bridges[i].island1 != NULL &&
            ((mx_strcmp(parsed_bridges[i].island1, bridge.island1) == 0 && mx_strcmp(parsed_bridges[i].island2, bridge.island2) == 0) ||
             (mx_strcmp(parsed_bridges[i].island1, bridge.island2) == 0 && mx_strcmp(parsed_bridges[i].island2, bridge.island1) == 0))) {
            return true;
        }
    }
    return false;
}

// Build a graph using the provided data.
static void build_graph(t_graph **graph, t_parsed_bridge *parsed_bridges, int num_of_bridges, char **islands, int num_of_islands) {
    *graph = mx_create_graph(num_of_islands);

    for (int i = 0; i < num_of_bridges; i++) {
        int src_index = find_index(islands, parsed_bridges[i].island1);
        int dst_index = find_index(islands, parsed_bridges[i].island2);

        mx_add_edge(*graph, parsed_bridges[i].island1, src_index, parsed_bridges[i].island2, dst_index, parsed_bridges[i].bridge_len);
    }
}

// Parse the input data and build a graph from it.
char **mx_parse_file(char *src, t_graph **graph) {
    // Split the input data into lines.
    char **lines = mx_strsplit(src, '\n');
    int num_of_bridges = count_bridges(lines);

    // Check and validate the number of islands in the first line of the input.
    if (lines[0] == NULL || !is_number_valid(lines[0]) || mx_atoi(lines[0]) <= 0) {
        mx_error_invalid_num_of_islands();
    }

    // Extract the number of islands from the first line.
    int num_of_islands = mx_atoi(lines[0]);

    // Create an array to store the names of the islands, with space for NULL.
    char **islands = malloc(sizeof(char *) * (num_of_islands + 1));
    islands[num_of_islands] = NULL;

    // Initialize counters and variables for parsing.
    int islands_counter = 0;

    // Create an array to store the parsed bridge information.
    t_parsed_bridge *parsed_bridges = malloc(sizeof(t_parsed_bridge) * num_of_bridges);

    for (int i = 1; lines[i] != NULL; i++) {
        parsed_bridges[i - 1] = parse_bridge(lines[i], i + 1);

        // Check for duplicate bridges.
        if (is_duplicate_bridge(parsed_bridges, i - 1, parsed_bridges[i - 1])) {
            mx_error_duplicate_bridges();
        }

        // Check and add the new islands to the list of islands.
        check_new_island(islands, num_of_islands, &islands_counter, parsed_bridges[i - 1].island1);
        check_new_island(islands, num_of_islands, &islands_counter, parsed_bridges[i - 1].island2);
    }

    // Build a graph using the extracted data.
    build_graph(graph, parsed_bridges, num_of_bridges, islands, num_of_islands);

    // Check the sum of bridge lengths for integer overflow.
    long long sum_bridges_len = 0;
    for (int i = 0; i < num_of_bridges; i++) {
        sum_bridges_len += parsed_bridges[i].bridge_len;
        if (sum_bridges_len > __INT_MAX__) {
            mx_error_sum_of_bridges_len_is_too_big();
        }
    }

    // Check that the number of unique islands matches the expected number.
    if (islands_counter != num_of_islands) {
        mx_error_invalid_num_of_islands();
    }

    // Free memory used by the lines array.
    mx_del_strarr(&lines);

    // Free memory used by the parsed bridges array.
    for (int i = 0; i < num_of_bridges; i++) {
        mx_strdel(&(parsed_bridges[i].island1));
        mx_strdel(&(parsed_bridges[i].island2));
    }
    free(parsed_bridges);

    // Return the array of island names.
    return islands;
}
