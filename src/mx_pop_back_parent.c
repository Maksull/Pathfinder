#include "../inc/pathfinder.h"

// Remove the last parent node from a linked list of parent nodes.
void mx_pop_back_parent(t_parent **head)
{
    // Check if the list or head is empty.
    if (head == NULL || *head == NULL)
    {
        return; // Nothing to remove.
    }

    // If there's only one node in the list, delete it and set head to NULL.
    if ((*head)->next == NULL)
    {
        free(*head);
        *head = NULL;
        return;
    }

    // Traverse the list to find the second-to-last node.
    t_parent *tmp = *head;
    while (tmp && tmp->next->next != NULL)
    {
        tmp = tmp->next;
    }

    // Remove the last node by freeing its memory and updating the link in the previous node.
    free(tmp->next);
    tmp->next = NULL;
}
