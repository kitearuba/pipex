//
// Created by christian on 16/10/24.
//
#include "../include/pipex.h"

void free_2d_array(char **arr)
{
    int i = 0;

    if (!arr)
        return;  // Ensure the array exists

    while (arr[i])
    {
        free(arr[i]);  // Free each element
        arr[i] = NULL;  // Set the pointer to NULL to avoid double free
        i++;
    }

    free(arr);  // Finally, free the array itself
    arr = NULL;  // Set the pointer to NULL to avoid double free
}