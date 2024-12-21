/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:04:28 by chrrodri          #+#    #+#             */
/*   Updated: 2024/12/21 21:24:29 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

/* ************************************************************************** */
/*                         Path Resolution Helpers                            */
/* ************************************************************************** */

/**
 * get_path_dirs - Splits the PATH environment variable into directories.
 * @pipex: Pointer to the pipex structure for error handling.
 * Returns:
 * - Array of directory strings if successful.
 * - Exits with an error message if the PATH is not found or split fails.
 */
static char	**get_path_dirs(t_pipex *pipex)
{
	char	*path;
	char	**dirs;

	path = getenv("PATH");
	if (!path)
		free_resources_on_error(pipex,
			"PATH environment variable not found", 1);
	dirs = ft_split(path, ':');
	if (!dirs)
		free_resources_on_error(pipex,
			"Failed to split PATH into directories", 1);
	return (dirs);
}

/**
 * construct_cmd_path - Combines a directory and command into a full path.
 * @dir: Directory path.
 * @cmd: Command name.
 * Returns:
 * - Newly allocated string with the full path.
 * - NULL if memory allocation fails.
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
 * search_in_path - Searches for an executable command in PATH directories.
 * @pipex: Pointer to the pipex structure for error handling.
 * @dirs: Array of directories in the PATH.
 * @cmd: Command name.
 * Returns:
 * - Full path of the executable command.
 * - Exits with an error message if the command is not found.
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

/* ************************************************************************** */
/*                          Main Path Resolution                              */
/* ************************************************************************** */

/**
 * get_cmd_path - Resolves the full path of a command.
 * @pipex: Pointer to the pipex structure for error handling.
 * @cmd: Command name or relative/absolute path.
 * Returns:
 * - Full path of the command if executable.
 * - Exits with an error if the command is not found or not executable.
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
