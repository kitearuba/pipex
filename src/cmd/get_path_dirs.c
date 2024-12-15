/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_dirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:04:28 by chrrodri          #+#    #+#             */
/*   Updated: 2024/11/21 19:43:59 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

/**
 * Retrieves directories from the PATH environment variable.
 * @cmd_path: Pointer to a buffer where the command path will be stored.
 *
 * Description:
 * - Fetches the PATH environment variable using getenv.
 * - Allocates memory for the command path buffer.
 * - Splits the PATH into an array of directories using ft_split.
 *
 * Returns:
 * - A pointer to a NULL-terminated array of directory strings.
 * - Exits with an error message if memory allocation or splitting fails.
 */
char	**get_path_dirs(char **cmd_path)
{
	char	*path;
	char	**dirs;

	path = getenv("PATH");
	if (!path)
		fatal_error("PATH not found in environment", NULL, 0);
	*cmd_path = malloc(4096);
	if (!*cmd_path)
		fatal_error("Memory allocation failed for command path", NULL, 1);
	dirs = ft_split(path, ':');
	if (!dirs)
	{
		free(*cmd_path);
		fatal_error("Failed to split PATH into directories", NULL, 1);
	}
	return (dirs);
}
