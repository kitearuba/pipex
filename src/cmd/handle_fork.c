/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:20:00 by chrrodri          #+#    #+#             */
/*   Updated: 2024/12/21 21:24:00 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"
/* ************************************************************************** */
/*                          Fork and Command Execution                        */
/* ************************************************************************** */

/**
 * handle_fork - Creates a child process for command execution.
 * @pipex: Pointer to the main pipex structure.
 * @cmd: Command to execute (parsed as arguments).
 * @index: Specifies if the function handles cmd1 (1) or cmd2 (2).
 * Description:
 * - Creates a child process using fork().
 * - Redirects input/output based on the command index.
 * - cmd1 (index == 1): Reads from infile, writes to the pipe's write end.
 * - cmd2 (index == 2): Reads from the pipe's read end, writes to outfile.
 * - Calls exec_cmd to execute the given command in the child process.
 * - Handles errors such as failed forks or redirection issues.
 * Returns:
 * - The process ID (pid) of the child process on success.
 * - Exits with error if fork or redirection fails.
 */
int	handle_fork(t_pipex *pipex, int index)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		free_resources_on_error(pipex, "Error forking", 1);
	if (pid == 0)
	{
		if (index == 1)
		{
			close(pipex->pipefd[0]);
			exec_cmd(pipex, pipex->infile, pipex->pipefd[1], pipex->cmd1);
		}
		else if (index == 2)
		{
			close(pipex->pipefd[1]);
			if (dup2(pipex->pipefd[0], STDIN_FILENO) < 0)
				free_resources_on_error(pipex,
					"Error redirecting pipe to stdin", 1);
			close(pipex->pipefd[0]);
			exec_cmd(pipex, STDIN_FILENO, pipex->outfile, pipex->cmd2);
		}
	}
	return (pid);
}
