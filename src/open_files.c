#include "../include/pipex.h"

void free_resources_on_error(t_pipex *pipex, const char *error_message)
{
    // Print error message
    perror(error_message);

    // Close file descriptors only if they were successfully opened
    if (pipex->file1 >= 0)
        close(pipex->file1);
    if (pipex->file2 >= 0)
        close(pipex->file2);

    // Free dynamically allocated memory only if it's not NULL
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

int open_files(char **argv, t_pipex *pipex)
{
    // Initialize file descriptors to -1 to check later if they were opened successfully
    pipex->file1 = -1;
    pipex->file2 = -1;

    // Attempt to open the input file
    pipex->file1 = open(argv[1], O_RDONLY);
    if (pipex->file1 < 0)
    {
        free_resources_on_error(pipex, "Error: Unable to open input file");
        return (1);
    }

    // Attempt to open the output file
    pipex->file2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (pipex->file2 < 0)
    {
        free_resources_on_error(pipex, "Error: Unable to open output file");
        return (1);
    }

    return (0);  // Success
}
