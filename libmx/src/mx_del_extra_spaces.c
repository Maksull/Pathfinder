#include "libmx.h"

char *mx_del_extra_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    int len = mx_strlen(str);
    int start = 0;
    int end = len - 1;

    while (start < len && mx_isspace(str[start])) {
        start++;
    }

    while (end >= 0 && mx_isspace(str[end])) {
        end--;
    }

    if (start > end) {
        return mx_strdup("");
    }

    char *result = (char *)malloc(end - start + 2);
    if (result == NULL) {
        return NULL;
    }

    int result_index = 0;

    for (int i = start; i <= end; i++) {
        if (mx_isspace(str[i])) {
            if (i > start && !mx_isspace(str[i - 1])) {
                result[result_index] = ' ';
                result_index++;
            }
        } else {
            result[result_index] = str[i];
            result_index++;
        }
    }

    result[result_index] = '\0';

    return result;
}
