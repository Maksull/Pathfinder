#include "libmx.h"

char *mx_strdup(const char *str)
{
    if (*str == '\0')
    {
        return NULL;
    }

    char *istr = mx_strnew(mx_strlen(str));
    mx_strcpy(istr, str);

    return istr;
}
