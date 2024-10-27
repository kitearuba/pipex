#include "../include/pipex.h"

int exec_cmd(t_pipex *pipex, int input_fd, int output_fd, char **cmd)
{
    char *cmd_path = get_cmd_path(cmd[0]);

    if (cmd_path == NULL)
    {
        ft_putstr_fd("Error: Command '", STDERR_FILENO);
        ft_putstr_fd(cmd[0], STDERR_FILENO);
        ft_putstr_fd("' not found\n", STDERR_FILENO);
        free_2d_array(cmd);  // Free memory when command not found
        return (1);
    }

    if (dup2(input_fd, STDIN_FILENO) < 0 || dup2(output_fd, STDOUT_FILENO) < 0)
    {
        free(cmd_path);
        free_2d_array(cmd);  // Free memory on dup2 error
        return error_handle("Error with dup2", pipex->pipefd);
    }

    close(pipex->pipefd[0]);
    close(pipex->pipefd[1]);
    execve(cmd_path, cmd, pipex->envp);
    perror("Error executing command");
    free(cmd_path);
    free_2d_array(cmd);  // Free memory on execve error
    exit(1);
}