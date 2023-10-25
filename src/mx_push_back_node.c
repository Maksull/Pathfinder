#include "../inc/pathfinder.h"

// Add a new node to the end of a linked list of nodes.
void mx_push_back_node(t_node **list, int index, char *name, int weight)
{
    // Create a new node.
    t_node *new_node = mx_create_node_in_graph(index, name, weight);

    // Find the last node in the linked list.
    t_node *last_node = *list;

    // If the list is empty, make the new node the head of the list.
    if (*list == NULL)
    {
        *list = new_node;
        return;
    }

    // Traverse the list to find the last node.
    while (last_node->next != NULL)
    {
        last_node = last_node->next;
    }

    // Add the new node to the end of the list.
    last_node->next = new_node;
}
