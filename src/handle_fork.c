#include "../include/pipex.h"

int handle_fork(t_pipex *pipex, char **cmd, int index)
{
    pid_t pid = fork();
    if (pid < 0)
        return error_handle("Error forking", pipex->pipefd);

    if (pid == 0) // Child process
    {
        if (index == 1)
        {
            close(pipex->pipefd[0]);  // Close the read end, not used in the first command
            return exec_cmd(pipex, pipex->file1, pipex->pipefd[1], cmd);
        }
        if (index == 2)
        {
            close(pipex->pipefd[1]);  // Close the write end, not used in the second command
            return exec_cmd(pipex, pipex->pipefd[0], pipex->file2, cmd);
        }
    }
    return (0); // Parent process
}
