#include "../include/pipex.h"

int create_pipe(int *pipefd)
{
    if (pipe(pipefd) == -1)
        return error_handle("Error creating pipe", pipefd);
    return (0);
}
