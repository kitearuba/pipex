#include "../include/pipex.h"

char *get_cmd_path(char *cmd)
{
    char *path;
    char *cmd_path;
    char **dirs;
    int i = 0;

    path = getenv("PATH");
    cmd_path = malloc(4096);  // Assuming max path length of 4096
    if (!path)
    {
        free(cmd_path);
        ft_putstr_fd("Error: PATH not found in environment\n", STDERR_FILENO);
        return (NULL);
    }
    dirs = ft_split(path, ':');
    if (!cmd_path || !dirs)
    {
        free(cmd_path);
        free_2d_array(dirs);  // Ensure dirs is freed
        return (NULL);
    }

    while (dirs[i])
    {
        ft_strlcpy(cmd_path, dirs[i], 4096);
        ft_strlcat(cmd_path, "/", 4096);
        ft_strlcat(cmd_path, cmd, 4096);
        if (access(cmd_path, X_OK) == 0)
        {
            free_2d_array(dirs);  // Free memory used for dirs
            return (cmd_path);
        }
        i++;
    }
    free(cmd_path);
    free_2d_array(dirs);  // Free memory used for dirs
    return (NULL);  // Command not found
}
