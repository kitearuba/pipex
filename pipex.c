#include "pipex.h"

int error_handle(char *str, int file1, int file2, int pipefd[])
{
    perror(str);
    if (file1 != -1) close(file1);
    if (file2 != -1) close(file2);
    if (pipefd != NULL)
    {
        close(pipefd[0]);
        close(pipefd[1]);
    }
    return (1);  // Return error value
}

int ft_create_pipe(char **argv, int *file1, int *file2, int pipefd[])
{
    *file1 = open(argv[1], O_RDONLY);  // Open file1 (input) in read-only mode
    if (*file1 < 0)
        return error_handle("Error opening file1", -1, -1, NULL);

    *file2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);  // Open file2 (output)
    if (*file2 < 0)
        return error_handle("Error opening file2", *file1, -1, NULL);

    if (pipe(pipefd) == -1)
        return error_handle("Error creating pipe", *file1, *file2, pipefd);

    return (0);  // Success
}

int fork_cmd(int file1, int file2, int pipefd[], char **cmd, int index)
{
    pid_t pid;

    pid = fork();// Fork the process to create a child
    if (pid < 0)
        return error_handle("Error forking", file1, file2, pipefd);
    if (pid == 0 && index == 1)  // Child process for cmd1
    {
        // Redirect input from file1
        dup2(file1, STDIN_FILENO);  // file1 becomes stdin
        dup2(pipefd[1], STDOUT_FILENO);  // pipefd[1] becomes stdout
        close(file1);
        close(file2);
        close(pipefd[0]);  // Close unused read end of the pipe
        close(pipefd[1]);

        execve(cmd[0], cmd, NULL);  // Execute cmd1 (cmd will be set correctly later)
        perror("Error executing cmd1");
        exit(1);
    }
    else if (pid == 0 && index == 2)  // Child process for cmd2
    {
        dup2(pipefd[0], STDIN_FILENO);  // pipefd[0] becomes stdin
        dup2(file2, STDOUT_FILENO);  // file2 becomes stdout
        close(file1);
        close(file2);
        close(pipefd[0]);
        close(pipefd[1]);

        execve(cmd[0], cmd, NULL);  // Execute cmd2 (cmd will be set correctly later)
        perror("Error executing cmd2");
        exit(1);
    }
    return (0);  // Success for fork
}

void
int main(int argc, char **argv)
{
    int     file1;
    int     file2;
    int     pipefd[2];  // Array for storing the two ends of the pipe
    char    **cmd1;
    char    **cmd2;

    if (argc != 5) // Checking for correct number of arguments
    {
        write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 36);
        return (1); // Return error if wrong number of arguments
    }
// Split the command strings into arrays of arguments
    cmd1 = ft_split(argv[2], ' ');  // Split cmd1 into array
    cmd2 = ft_split(argv[3], ' ');  // Split cmd2 into array

    // Create the pipe and open files
    if (ft_create_pipe(argv, &file1, &file2, pipefd))
        return (1);  // Return if pipe creation or file opening fails

    // Fork and execute the first command (cmd1)
    if (fork_cmd(file1, file2, pipefd, cmd1, 1))
        return (1);  // Return if fork or execution fails for cmd1

    // Fork and execute the second command (cmd2)
    if (fork_cmd(file1, file2, pipefd, cmd2, 2))
        return (1);  // Return if fork or execution fails for cmd2

    // Close the pipes and files in the parent
    close(pipefd[0]);
    close(pipefd[1]);
    close(file1);
    close(file2);

    // Wait for both child processes to finish
    wait(NULL);
    wait(NULL);

    // Free the memory for cmd1 and cmd2 arrays
    free(cmd1);
    free(cmd2);

    return (0);
}


