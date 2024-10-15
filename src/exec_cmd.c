#include "../include/pipex.h"

int exec_cmd(t_pipex *pipex, int input_fd, int output_fd, char **cmd)
{
    char *cmd_path = get_cmd_path(cmd[0]);

    if (cmd_path == NULL)
    {
        error_handle("Error: Command not found", pipex->pipefd);
        return (1);
    }

    if (dup2(input_fd, STDIN_FILENO) < 0 || dup2(output_fd, STDOUT_FILENO) < 0)
    {
        free(cmd_path);
        return error_handle("Error with dup2", pipex->pipefd);
    }

    close(pipex->pipefd[0]);
    close(pipex->pipefd[1]);
    execve(cmd_path, cmd, pipex->envp);
    perror("Error executing command");
    free(cmd_path);
    exit(1);
}