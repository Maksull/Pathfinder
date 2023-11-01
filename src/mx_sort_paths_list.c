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

// Add a path to the end of the list
void mx_push_back_path(t_path **list, int weight) {
    t_path *new_path = mx_create_path(weight);
    if (*list == NULL) {
        *list = new_path;
    } else {
        t_path *current = *list;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_path;
    }
}

// Compare two paths and return true if the first path is greater
bool compare_paths(t_node *list1, t_node *list2) {
    bool is_greater = false;
    while (list1 != NULL && list2 != NULL) {
        if (list2->index > list1->index) {
            is_greater = true;
        }
        if (list1->index > list2->index && !is_greater) {
            return true;
        }
        list1 = list1->next;
        list2 = list2->next;
    }
    return false;
}

static t_path *merge(t_path *left, t_path *right) {
    t_path *result = NULL;

    while (left && right) {
        if (compare_paths(left->list, right->list)) {
            mx_push_front_path(&result, left->weight);
            left = left->next;
        } else {
            mx_push_front_path(&result, right->weight);
            right = right->next;
        }
    }

    while (left) {
        mx_push_front_path(&result, left->weight);
        left = left->next;
    }

    while (right) {
        mx_push_front_path(&result, right->weight);
        right = right->next;
    }

    return result;
}

static t_path *merge_sort(t_path *list) {
    if (!list || !list->next) {
        return list;
    }

    t_path *left = NULL;
    t_path *right = NULL;
    t_path *current = list;
    int size = list_of_paths_size(list) / 2;

    for (int i = 0; i < size; i++) {
        mx_push_back_path(&left, current->weight);
        current = current->next;
    }

    while (current) {
        mx_push_back_path(&right, current->weight);
        current = current->next;
    }

    left = merge_sort(left);
    right = merge_sort(right);

    return merge(left, right);
}

t_path *mx_sort_paths_list(t_path *list) {
    if (!list) {
        return NULL;
    }

    return merge_sort(list);
}
