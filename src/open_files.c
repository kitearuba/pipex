#include "../include/pipex.h"

int open_files(char **argv, t_pipex *pipex)
{
    pipex->file1 = open(argv[1], O_RDONLY);  // Open input file in read-only mode
    if (pipex->file1 < 0)
    {
        perror("Error opening input file");
        if (pipex->cmd1)
        {
            free_2d_array(pipex->cmd1);  // Free cmd1
            pipex->cmd1 = NULL;  // Set to NULL to avoid double free
        }
        if (pipex->cmd2)
        {
            free_2d_array(pipex->cmd2);  // Free cmd2
            pipex->cmd2 = NULL;  // Set to NULL to avoid double free
        }
        return (1);
    }
    pipex->file2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);  // Open output file
    if (pipex->file2 < 0)
    {
        close(pipex->file1);  // Close input file on error
        perror("Error opening input file");
        if (pipex->cmd1)
        {
            free_2d_array(pipex->cmd1);  // Free cmd1
            pipex->cmd1 = NULL;  // Set to NULL to avoid double free
        }
        if (pipex->cmd2)
        {
            free_2d_array(pipex->cmd2);  // Free cmd2
            pipex->cmd2 = NULL;  // Set to NULL to avoid double free
        }
        return (1);
    }
    return (0);  // Success
}
