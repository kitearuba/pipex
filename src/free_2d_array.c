//
// Created by christian on 16/10/24.
//
#include "../include/pipex.h"

void free_2d_array(char **array)
{
    int i = 0;

    if (!array)
        return;

    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);  // Free the array itself
}