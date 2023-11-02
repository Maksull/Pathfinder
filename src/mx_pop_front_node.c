#include "../inc/pathfinder.h"

// Function to remove the first node from the list and update the list head.
void mx_pop_front_node(t_node **head) {
    if (head && *head) {
        if ((*head)->next == NULL) {
            mx_del_node(head); // If the list contains only one node, delete it and update the list head.
            return;
        }

        t_node *tmp = *head; // Store a reference to the first node.
        *head = (*head)->next; // Update the list head to point to the second node.

        mx_del_node(&tmp); // Delete the first node to prevent memory leaks.
    }
}
