/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_on_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:31:36 by chrrodri          #+#    #+#             */
/*   Updated: 2024/12/21 21:27:48 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

/* ************************************************************************** */
/*                          Error Handling & Cleanup                          */
/* ************************************************************************** */

/**
 * free_resources_on_error - Cleans up resources and exits on error.
 * @pipex: Pointer to the pipex structure for resource tracking.
 * @error_message: Message to display for the error.
 * @exit_code: Exit code for the program.
 * Description:
 * - Frees allocated memory (e.g., command arrays).
 * - Closes open file descriptors (infile, outfile, pipe ends).
 * - Prints the error message and exits with the specified code.
 */
void	free_resources_on_error(t_pipex *pipex, const char *error_message,
	int exit_code)
{
	if (pipex->cmd1)
		free_2d_array(pipex->cmd1);
	if (pipex->cmd2)
		free_2d_array(pipex->cmd2);
	if (pipex->infile >= 0)
		close(pipex->infile);
	if (pipex->outfile >= 0)
		close(pipex->outfile);
	if (pipex->pipefd[0] >= 0)
		close(pipex->pipefd[0]);
	if (pipex->pipefd[1] >= 0)
		close(pipex->pipefd[1]);
	if (error_message && *error_message)
		ft_printf_fd(STDERR_FILENO, "pipex: %s", error_message);
	if (errno)
		ft_printf_fd(STDERR_FILENO, ": %s", strerror(errno));
	ft_printf_fd(STDERR_FILENO, "\n");
	exit(exit_code);
}
