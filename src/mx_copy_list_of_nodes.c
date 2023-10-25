#include "../inc/pathfinder.h"

// Copy the list of vertices from the source list to the destination list.
void mx_copy_list_of_node(t_node **dest, t_node *src)
{
    if (dest != NULL && *dest != NULL)
    {
        // Clear and free the destination list if it is not empty.
        mx_clear_list_of_nodes(&(*dest));
        *dest = NULL;
    }

    // Iterate through the source list and create new vertices in the destination list.
    while (src)
    {
        mx_push_back_node(dest, src->index, src->name, src->weight);
        src = src->next;
    }
}
