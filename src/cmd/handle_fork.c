/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:20:00 by chrrodri          #+#    #+#             */
/*   Updated: 2024/12/08 23:07:14 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

/**
 * handle_fork - Manages the creation of child processes for command execution.
 *
 * @pipex: Pointer to the main pipex structure.
 * @cmd: Command to execute (parsed as arguments).
 * @index: Indicates whether the function handles cmd1 (1) or cmd2 (2).
 *
 * Description:
 * - Creates a child process using fork().
 * - cmd1 (index == 1): Redirects input from file1 and output to the pipe's 
 *   write end.
 * - cmd2 (index == 2): Redirects input from the pipe's read end and output to 
 *   file2.
 * - Calls exec_cmd to execute the given command in the child process.
 * - Handles errors such as failed forks or redirection issues.
 *
 * Returns:
 * - 0 on success.
 * - Non-zero if an error occurs during forking or redirection.
 */
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
			exec_cmd(pipex, pipex->file1, pipex->pipefd[1], cmd);
		}
		if (index == 2)
		{
			close(pipex->pipefd[1]);
			if (dup2(pipex->pipefd[0], STDIN_FILENO) < 0)
				fatal_error("Error redirecting pipe to stdin", NULL, 1);
			close(pipex->pipefd[0]);
			exec_cmd(pipex, STDIN_FILENO, pipex->file2, cmd);
		}
	}
	return (0);
}
