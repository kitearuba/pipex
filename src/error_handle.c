#include "../include/pipex.h"

int error_handle(char *str, int *pipefd)
{
    perror(str);
    if (pipefd != NULL)
    {
        close(pipefd[0]);
        close(pipefd[1]);
    }
    return (1);  // Return error value
}
