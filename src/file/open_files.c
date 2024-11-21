/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:19:17 by chrrodri          #+#    #+#             */
/*   Updated: 2024/11/20 22:33:00 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

int	open_files(char **argv, t_pipex *pipex)
{
	pipex->file1 = -1;
	pipex->file2 = -1;
	pipex->file1 = open(argv[1], O_RDONLY);
	if (pipex->file1 < 0)
	{
		free_resources_on_error(pipex, "Error: Unable to open input file");
		return (1);
	}
	pipex->file2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->file2 < 0)
	{
		free_resources_on_error(pipex, "Error: Unable to open output file");
		return (1);
	}
	return (0);
}
