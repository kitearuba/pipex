/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:04:28 by chrrodri          #+#    #+#             */
/*   Updated: 2024/11/21 19:39:30 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

static char	*construct_cmd_path(char *dir, char *cmd)
{
	char	*cmd_path;
	size_t	len;

	len = ft_strlen(dir) + ft_strlen(cmd) + 2;
	cmd_path = malloc(len);
	if (cmd_path)
	{
		ft_strlcpy(cmd_path, dir, len);
		ft_strlcat(cmd_path, "/", len);
		ft_strlcat(cmd_path, cmd, len);
	}
	return (cmd_path);
}

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

char	*get_cmd_path(char *cmd)
{
	// Handle absolute paths and paths starting with "./"
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd)); // Command is valid and executable
		ft_printf_fd(STDERR_FILENO, "pipex: %s: %s\n", cmd, strerror(errno));
		return (NULL);
	}
	char	*cmd_path;
	char	**dirs;
	char	*result;

	dirs = get_path_dirs(&cmd_path);
	if (!dirs)
		return (NULL);
	result = try_path(dirs, cmd, &cmd_path);
	if (!result)
	{
		free(cmd_path);
		free_2d_array(dirs);
		ft_printf_fd(STDERR_FILENO, "pipex: %s: command not found\n", cmd);
	}
	return (result);
}
