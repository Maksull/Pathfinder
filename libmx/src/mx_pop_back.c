#include "libmx.h"

void mx_pop_back(t_list **head) {
    if (*head == NULL) {
        return;
    }

    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }

    t_list *second_to_last = *head;
    while (second_to_last->next->next != NULL) {
        second_to_last = second_to_last->next;
    }

    free(second_to_last->next);
    second_to_last->next = NULL;
}
