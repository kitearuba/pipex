#

int main(int argc, char **argv, char **envp)
{
    int file1, file2, pipefd[2];
    char **cmd1, **cmd2;

    if (argc != 5)
    {
        write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 36);
        return (1);
    }

    cmd1 = ft_split(argv[2], ' ');
    cmd2 = ft_split(argv[3], ' ');

    if (open_files(argv, &file1, &file2) || create_pipe(pipefd))
        return (1);

    if (handle_fork(file1, file2, pipefd, cmd1, 1, envp) || handle_fork(file1, file2, pipefd, cmd2, 2, envp))
        return (1);

    close(pipefd[0]);
    close(pipefd[1]);
    close(file1);
    close(file2);
    wait(NULL);
    wait(NULL);
    free_2d_array(cmd1);  // Free 2D array
    free_2d_array(cmd2);  // Free 2D array

    return (0);
}