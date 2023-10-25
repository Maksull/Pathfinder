#include "../inc/pathfinder.h"

// Custom implementation of the atoi function to convert a string to an integer.
int mx_atoi(const char *str)
{
    int result = 0;
    int sign = 1;   
    int i = 0;      

    // Skip leading white spaces.
    while (mx_isspace(str[i]))
    {
        i++;
    }

    // Check for a sign character ('-' for negative, '+' or none for positive).
    if (str[i] == '-' || str[i] == '+')
    {
        sign = 1 - 2 * (str[i++] == '-'); // Adjust the sign based on '-' character.
    }

    // Convert consecutive digits to an integer.
    while (mx_isdigit(str[i]))
    {
        result = result * 10 + (str[i++] - 48); // Convert character to integer and accumulate.
    }

    return result * sign; // Return the final result with the sign applied.
}
