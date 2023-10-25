#include "libmx.h"

int mx_partition(char **arr, int left, int right) {
    int pivot = (left + right) / 2;
    int i = left;
    int j = right;

    while (i <= j) {
        while (mx_strlen(arr[i]) < mx_strlen(arr[pivot]))
            i++;
        while (mx_strlen(arr[j]) > mx_strlen(arr[pivot]))
            j--;

        if (i <= j) {
            char *temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }

    return i;
}

int mx_quicksort(char **arr, int left, int right) {
    if (arr == NULL)
        return -1;

    int swaps = 0;

    if (left < right) {
        int pivotIndex = mx_partition(arr, left, right);
        swaps += mx_quicksort(arr, left, pivotIndex - 1);
        swaps += mx_quicksort(arr, pivotIndex, right);
    }

    return swaps;
}
