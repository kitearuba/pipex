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

void	free_resources_on_error(t_pipex *pipex, const char *error_message, int exit_code)
{
	if (pipex->cmd1)
		free_2d_array(pipex->cmd1);
	if (pipex->cmd2)
		free_2d_array(pipex->cmd2);
	if (pipex->infile >= 0)
		close(pipex->infile);
	if (pipex->outfile >= 0)
		close(pipex->outfile);
	if (pipex->pipefd[0] >= 0) // Close read end of pipe if open
		close(pipex->pipefd[0]);
	if (pipex->pipefd[1] >= 0) // Close write end of pipe if open
		close(pipex->pipefd[1]);
	/* Error message printing */
	if (error_message && *error_message)
		ft_printf_fd(STDERR_FILENO,"pipex: %s", error_message);
	if (errno)
		ft_printf_fd(STDERR_FILENO,": %s", strerror(errno));
	ft_printf_fd(STDERR_FILENO, "\n");
	exit(exit_code);
}
