/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_on_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:31:36 by chrrodri          #+#    #+#             */
/*   Updated: 2024/11/21 21:16:52 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"º

void	free_resources_on_error(t_pipex *pipex, const char *error_message)
{
	if (pipex->file1 >= 0)
		close(pipex->file1);
	if (pipex->file2 >= 0)
		close(pipex->file2);
	if (pipex->cmd1)
	{
		free_2d_array(pipex->cmd1);
		pipex->cmd1 = NULL;
	}
	if (pipex->cmd2)
	{
		free_2d_array(pipex->cmd2);
		pipex->cmd2 = NULL;
	}
	fatal_error(error_message, NULL, 1);
}
