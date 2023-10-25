#include "../inc/pathfinder.h"

// Check if a path with the same vertices already exists in the list of paths.
bool mx_is_path_saved(t_path *paths, t_node *new_path)
{
    t_path *path = paths;

    while (path != NULL)
    {
        // Get the list of vertices in the current path.
        t_node *list = paths->list;
        // Get the list of vertices in the new path to compare.
        t_node *new_list = new_path;

        // Assume the paths are saved until proven otherwise.
        bool is_saved = true;

        // Compare the sizes of the node lists; if different, they can't be the same path.
        if (mx_list_of_node_size(list) != mx_list_of_node_size(new_list))
        {
            is_saved = false;
        }

        // Traverse and compare vertices in both lists.
        while (list != NULL && new_list != NULL && is_saved)
        {
            // If the indices of the vertices differ, the paths are different.
            if (list->index != new_list->index)
            {
                is_saved = false;
                break;
            }

            list = list->next;
            new_list = new_list->next;
        }

        // If 'is_saved' remains true, the paths are the same, so return true.
        if (is_saved)
        {
            return true;
        }

        // Move to the next path and continue the loop.
        path = path->next;
    }

    // If the new path is not found in the list, return false.
    return false;
}
