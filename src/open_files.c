#include "../include/pipex.h"

int open_files(char **argv, t_pipex *pipex)
{
    pipex->file1 = open(argv[1], O_RDONLY);  // Open input file in read-only mode
    if (pipex->file1 < 0)
        return (error_handle("Error opening input file", NULL));

    pipex->file2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);  // Open output file
    if (pipex->file2 < 0)
    {
        close(pipex->file1);
        return (error_handle("Error opening output file", NULL));
    }
    return (0);  // Success
}
