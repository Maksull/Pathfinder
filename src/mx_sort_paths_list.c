#include "../inc/pathfinder.h"

// Function to calculate the size of the list of paths.
int list_of_paths_size(t_path *list) {
    int size = 0;
    t_path *current = list;
    while (current != NULL) {
        size++;
        current = current->next;
    }
    return size;
}

// Add a path to the end of the list.
void mx_push_back_path(t_path **list, int weight) {
    t_path *new_path = mx_create_path(weight);
    if (*list == NULL) {
        *list = new_path; // If the list is empty, set the new path as the head.
    } else {
        t_path *current = *list;
        while (current->next != NULL) {
            current = current->next; // Traverse the list to find the last path.
        }
        current->next = new_path; // Append the new path to the end.
    }
}

// Compare two paths and return true if the first path is greater.
bool compare_paths(t_node *list1, t_node *list2) {
    bool is_greater = false;
    while (list1 != NULL && list2 != NULL) {
        if (list2->index > list1->index) {
            is_greater = true;
        }
        if (list1->index > list2->index && !is_greater) {
            return true; // If the indices differ, return true if list1's index is greater.
        }
        list1 = list1->next;
        list2 = list2->next;
    }
    return false; // Return false if both paths are identical or list2 is greater.
}

// Merge two sorted paths into a single sorted path.
static t_path *merge(t_path *left, t_path *right) {
    t_path *result = NULL;

    while (left && right) {
        if (compare_paths(left->list, right->list)) {
            mx_push_front_path(&result, left->weight); // Add the path from the 'left' list to the result.
            left = left->next;
        } else {
            mx_push_front_path(&result, right->weight); // Add the path from the 'right' list to the result.
            right = right->next;
        }
    }

    // Append any remaining paths from the 'left' and 'right' lists.
    while (left) {
        mx_push_front_path(&result, left->weight);
        left = left->next;
    }

    while (right) {
        mx_push_front_path(&result, right->weight);
        right = right->next;
    }

    return result; // Return the merged and sorted path.
}

// Sort the list of paths using merge sort.
static t_path *merge_sort(t_path *list) {
    if (!list || !list->next) {
        return list; // Base case: Return the list if it's empty or contains a single path.
    }

    t_path *left = NULL;
    t_path *right = NULL;
    t_path *current = list;
    int size = list_of_paths_size(list) / 2;

    // Split the list into 'left' and 'right' sublists of approximately equal size.
    for (int i = 0; i < size; i++) {
        mx_push_back_path(&left, current->weight);
        current = current->next;
    }

    while (current) {
        mx_push_back_path(&right, current->weight);
        current = current->next;
    }

    // Recursively sort and merge the 'left' and 'right' sublists.
    left = merge_sort(left);
    right = merge_sort(right);

    return merge(left, right); // Merge and return the sorted result.
}

// Public function to sort the list of paths using merge sort.
t_path *mx_sort_paths_list(t_path *list) {
    if (!list) {
        return NULL;
    }

    return merge_sort(list); // Call the merge sort function to sort the list of paths.
}
