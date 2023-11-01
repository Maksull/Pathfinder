#include "../inc/pathfinder.h"

void mx_pop_front_node(t_node **head) {
    if (head && *head) {
        if ((*head)->next == NULL) {
            mx_del_node(head);
            return;
        }

        t_node *tmp = *head;
        *head = (*head)->next;

        mx_del_node(&tmp);
    }
}
