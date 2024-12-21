/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:04:28 by chrrodri          #+#    #+#             */
/*   Updated: 2024/12/16 14:46:07 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

static char	**get_path_dirs(t_pipex *pipex)
{
	char	*path;
	char	**dirs;

	path = getenv("PATH");
	if (!path)
		free_resources_on_error(pipex, "PATH environment variable not found", 1);
	dirs = ft_split(path, ':');
	if (!dirs)
		free_resources_on_error(pipex, "Failed to split PATH into directories", 1);
	return (dirs);
}

/**
 * Constructs a command path by combining a directory and a command.
 * @dir: Directory path.
 * @cmd: Command name. 
 * Returns: Newly allocated string with the full path, or NULL on failure.
 */
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
 * Returns: Newly allocated string with the cmd's full path, if not found NULL.
 */
static char	*search_in_path(t_pipex *pipex, char **dirs, char *cmd)
{
	char	*candidate;
	int		i;

	i = 0;
	while (dirs[i])
	{
		candidate = construct_cmd_path(dirs[i], cmd);
		if (candidate && access(candidate, X_OK) == 0)
		{
			free_2d_array(dirs);
			return (candidate);
		}
		free(candidate);
		i++;
	}
	free_2d_array(dirs);
	free_resources_on_error(pipex, "Command not found", 127);
	return (NULL);
}

/**
 * Resolves the full path of a command.
 * @cmd: Command name or relative/absolute path.
 * Returns: Newly allocated string with the cmd's full path, NULL if not found.
 */
char	*get_cmd_path(t_pipex *pipex, char *cmd)
{
	char	**dirs;

	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		free_resources_on_error(pipex, "Command not executable", 127);
	}
	dirs = get_path_dirs(pipex);
	return (search_in_path(pipex, dirs, cmd));
}
