#include "../inc/pathfinder.h"

// Function to print an error message for incorrect program usage
void mx_error_wrong_usage() 
{
    mx_printerror("usage: ./pathfinder [filename]\n");
    exit(-1);
}

// Function to print an error message for a non-existent file
void mx_error_file_not_exist(const char *filename)
{
    mx_printerror("error: file ");
    mx_printerror(filename);
    mx_printerror(" does not exist\n");
    exit(-1);
}

// Function to print an error message for an empty file
void mx_error_file_empty(const char *filename)
{
    mx_printerror("error: file ");
    mx_printerror(filename);
    mx_printerror(" is empty\n");
    exit(-1);
}

// Function to print an error message for an invalid line in the file
void mx_error_line_not_valid(int index)
{
    mx_printerror("error: line ");
    mx_printerror(mx_itoa(index));
    mx_printerror(" is not valid\n");
    exit(-1);
}

// Function to print an error message for an invalid number of islands
void mx_error_invalid_num_of_islands()
{
    mx_printerror("error: invalid number of islands\n");
    exit(-1);
}

// Function to print an error message for duplicate bridges
void mx_error_duplicate_bridges()
{
    mx_printerror("error: duplicate bridges\n");
    exit(-1);
}

// Function to print an error message for a sum of bridge lengths that is too large
void mx_error_sum_of_bridges_len_is_too_big()
{
    mx_printerror("error: sum of bridges lengths is too big\n");
    exit(-1);
}
