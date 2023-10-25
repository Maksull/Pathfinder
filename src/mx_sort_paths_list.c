#include "../inc/pathfinder.h"

// Comparator function to compare two vertices based on their indices.
static bool compare(t_node *vertex1, t_node *vertex2) {
    return vertex1->index > vertex2->index;
}

// Merge two sorted path lists into a single sorted list.
static t_path* merge_paths(t_path *left, t_path *right) {
    t_path dummy;
    t_path *tail = &dummy;
    dummy.next = NULL;

    // Merge the two sorted path lists.
    while (left && right) {
        if (compare(left->list, right->list)) {
            tail->next = left;
            left = left->next;
        } else {
            tail->next = right;
            right = right->next;
        }
        tail = tail->next;
    }

    // Attach any remaining elements to the merged list.
    tail->next = (left != NULL) ? left : right;

    return dummy.next;
}

// Split a path list into two halves.
static void split_path_list(t_path *head, t_path **left, t_path **right) {
    t_path *slow = head;
    t_path *fast = head->next;

    // Use the slow and fast pointer technique to split the list into two halves.
    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *left = head;
    *right = slow->next;
    slow->next = NULL;
}

// Sort a list of paths using merge sort.
t_path *mx_sort_paths_list(t_path *list) {
    if (list == NULL || list->next == NULL) {
        return list; // Base case: If the list is empty or has one element, it's already sorted.
    }

    t_path *left;
    t_path *right;
    split_path_list(list, &left, &right); // Split the list into two halves.

    left = mx_sort_paths_list(left); // Recursively sort the left half.
    right = mx_sort_paths_list(right); // Recursively sort the right half.

    return merge_paths(left, right); // Merge the two sorted halves into a single sorted list.
}
