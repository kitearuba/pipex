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

char *get_cmd_path(char *cmd)
{
	char *cmd_path;
	char **dirs;
	int i;

	dirs = get_path_dirs(&cmd_path);
	if (!dirs)
		return (NULL);
	i = 0;
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
