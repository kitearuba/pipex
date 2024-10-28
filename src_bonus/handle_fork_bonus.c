#include "../include/pipex.h"

int handle_fork(t_pipex *pipex, char **cmd, int index)
{
    pid_t pid = fork();  // Fork the process to create a child
    if (pid < 0)
        return error_handle("Error forking", pipex->pipefd);

    if (pid == 0)
    {
        if (index == 1)
            return exec_cmd(pipex, pipex->file1, pipex->pipefd[1], cmd);
        if (index == 2)
            return exec_cmd(pipex, pipex->pipefd[0], pipex->file2, cmd);
    }
    return (0);  // Parent process
}

