#include "../include/pipex.h"

char *get_cmd_path(char *cmd)
{
    char *path = getenv("PATH");
    char *cmd_path = malloc(4096);  // Assuming max path length of 4096
    char **dirs = ft_split(path, ':');
    int i = 0;

    if (!cmd_path || !dirs)
        return (NULL);

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
