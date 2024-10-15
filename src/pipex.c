#include "../include/pipex.h"

int main(int argc, char **argv, char **envp)
{
    t_pipex pipex;

    if (argc != 5)
    {
        write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 36);
        return (1);
    }

    pipex.envp = envp;
    pipex.cmd1 = ft_split(argv[2], ' ');
    pipex.cmd2 = ft_split(argv[3], ' ');

    if (open_files(argv, &pipex) || create_pipe(pipex.pipefd))
        return (1);

    if (handle_fork(&pipex, pipex.cmd1, 1) || handle_fork(&pipex, pipex.cmd2, 2))
        return (1);

    close(pipex.pipefd[0]);
    close(pipex.pipefd[1]);
    close(pipex.file1);
    close(pipex.file2);
    wait(NULL);
    wait(NULL);
    free_2d_array(pipex.cmd1);
    free_2d_array(pipex.cmd2);

    return (0);
}