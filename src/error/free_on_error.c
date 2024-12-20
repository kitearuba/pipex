/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_on_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:31:36 by chrrodri          #+#    #+#             */
/*   Updated: 2024/12/08 18:34:37 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	free_resources_on_error(t_pipex *pipex, const char *error_message)
{
	if (pipex->infile >= 0)
		close(pipex->infile);
	if (pipex->outfile >= 0)
		close(pipex->outfile);
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
