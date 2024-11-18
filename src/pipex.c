//
// Created by christian on 29/10/24.
//
#include "../include/pipex.h"

void free_pipex(t_pipex *pipex)
{
    if (pipex->cmd1)
    {
        free_2d_array(pipex->cmd1);
        pipex->cmd1 = NULL;
    }
    if (pipex->cmd2)
    {
        free_2d_array(pipex->cmd2);
        pipex->cmd2 = NULL;
    }
}

int init_pipex(t_pipex *pipex, char **argv, char **envp)
{
    pipex->envp = envp;
    pipex->cmd1 = ft_split(argv[2], ' ');
    pipex->cmd2 = ft_split(argv[3], ' ');
    if (!pipex->cmd1 || !pipex->cmd2)
        return (1);
    return (0);
}

int main(int argc, char **argv, char **envp)
{
    t_pipex pipex;

    if (argc != 5)
    {
        ft_printf("Usage: ./pipex file1 cmd1 cmd2 file2\n");
        return (1);
    }

    if (init_pipex(&pipex, argv, envp) || open_files(argv, &pipex) || create_pipe(pipex.pipefd))
    {
        free_pipex(&pipex);
        return (1);
    }

    // Execute commands
    if (handle_fork(&pipex, pipex.cmd1, 1) || handle_fork(&pipex, pipex.cmd2, 2))
    {
        free_pipex(&pipex);
        return (1);
    }

    free_pipex(&pipex); // Free allocated resources
    return (0);
}