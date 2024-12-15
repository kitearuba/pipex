/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:04:28 by chrrodri          #+#    #+#             */
/*   Updated: 2024/12/15 22:27:01 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

/**
 * Constructs a command path by combining a directory and a command.
 * @dir: Directory path.
 * @cmd: Command name.
 * Returns:
 * - A newly allocated string containing the full path, or NULL on failure.
 */
/* +2 for '/' and '\0' */
static char	*construct_cmd_path(char *dir, char *cmd)
{
	char	*cmd_path;
	size_t	len;

	len = ft_strlen(dir) + ft_strlen(cmd) + 2;
	cmd_path = malloc(len);
	if (!cmd_path)
		return (NULL);
	ft_strlcpy(cmd_path, dir, len);
	ft_strlcat(cmd_path, "/", len);
	ft_strlcat(cmd_path, cmd, len);
	return (cmd_path);
}

/**
 * Searches for the executable command in directories.
 * @dirs: Array of directories in the $PATH environment variable.
 * @cmd: Command name.
 * @cmd_path: Pointer to command path to free if necessary.
 * Returns:
 * - Newly allocated string with the command's full path, or NULL if not found.
 */
static char	*try_path(char **dirs, char *cmd, char **cmd_path)
{
	char	*candidate;
	int		i;

	i = 0;
	while (dirs[i])
	{
		candidate = construct_cmd_path(dirs[i], cmd);
		if (candidate && access(candidate, X_OK) == 0)
		{
			free(*cmd_path);
			free_2d_array(dirs);
			return (candidate);
		}
		free(candidate);
		i++;
	}
	return (NULL);
}

/**
 * Resolves the full path of a command.
 * @cmd: Command name or relative/absolute path.
 * Returns:
 * - Newly allocated string with the command's full path, or NULL if not found.
 */

char *get_cmd_path(char *cmd)
{
    char    *cmd_path;
    char    **dirs;
    char    *result;

    if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
    {
        if (access(cmd, X_OK) == 0)
            return (ft_strdup(cmd));
        ft_printf_fd(STDERR_FILENO, "pipex: %s: %s\n", cmd, strerror(errno));
        return (NULL);
    }
    dirs = get_path_dirs(&cmd_path);
    if (!dirs)
        return (NULL);
    result = try_path(dirs, cmd, &cmd_path);
    if (!result)
    {
        free(cmd_path);
        free_2d_array(dirs); // Free the directories array
        ft_printf_fd(STDERR_FILENO, "pipex: %s: command not found\n", cmd);
    }
    return (result);
}

