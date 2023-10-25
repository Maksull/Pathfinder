#include "../libmx/inc/libmx.h"

// Print an error message to the standard error stream.
void mx_printerror(const char *s)
{
    // Use the "write" system call to write the error message to the standard error (file descriptor 2).
    write(2, s, mx_strlen(s));
}
