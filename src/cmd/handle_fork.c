/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:20:00 by chrrodri          #+#    #+#             */
/*   Updated: 2024/11/22 11:20:17 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

int	handle_fork(t_pipex *pipex, char **cmd, int index)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (error_handle("Error forking", pipex->pipefd));
	if (pid == 0)
	{
		if (index == 1)
		{
			close(pipex->pipefd[0]);
			return (exec_cmd(pipex, pipex->file1, pipex->pipefd[1], cmd));
		}
		if (index == 2)
		{
			close(pipex->pipefd[1]);
			if (dup2(pipex->pipefd[0], STDIN_FILENO) < 0)
				fatal_error("Error redirecting pipe to stdin", NULL, 1);
			close(pipex->pipefd[0]);
			return (exec_cmd(pipex, STDIN_FILENO, pipex->file2, cmd));
		}
	}
	return (0);
}
