/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:04:28 by chrrodri          #+#    #+#             */
/*   Updated: 2024/11/20 22:08:55 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*get_cmd_path(char *cmd)
{
	char	*path;
	char	*cmd_path;
	char	**dirs;
	int		i;

	i = 0;
	path = getenv("PATH");
	cmd_path = malloc(4096);
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
		free_2d_array(dirs);
		return (NULL);
	}
	while (dirs[i])
	{
		ft_strlcpy(cmd_path, dirs[i], 4096);
		ft_strlcat(cmd_path, "/", 4096);
		ft_strlcat(cmd_path, cmd, 4096);
		if (access(cmd_path, X_OK) == 0)
		{
			free_2d_array(dirs);
			return (cmd_path);
		}
		i++;
	}
	free(cmd_path);
	free_2d_array(dirs);
	return (NULL);
}
