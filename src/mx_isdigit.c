#include "../inc/pathfinder.h"

// Check if an integer represents a digit character (0-9).
bool mx_isdigit(int c)
{
    if (c >= 48 && c <= 57)
    {
        return true;
    }
    return false;
}
