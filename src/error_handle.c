#include "../include/pipex.h"

int error_handle(char *str, int *pipefd)
{
    if (pipefd)
    {
        close(pipefd[0]);
        close(pipefd[1]);
    }
    // Use ft_printf to print the error message and strerror message
    ft_printf("%s: %s\n", str, strerror(errno));
    return (1);  // Return error value
}
