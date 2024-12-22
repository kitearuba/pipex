/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:50:31 by chrrodri          #+#    #+#             */
/*   Updated: 2024/12/22 16:12:08 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

/* ************************************************************************** */
/*                         Command Execution Function                         */
/* ************************************************************************** */

/**
 * exec_cmd - Executes a given command with redirected input/output.
 * @pipex: Pointer to the main pipex structure.
 * @input_fd: File descriptor for the command's input.
 * @output_fd: File descriptor for the command's output.
 * @cmd: Command and its arguments to execute.
 * Description:
 * - Resolves the command's absolute path using get_cmd_path.
 * - Redirects input/output using dup2.
 * - Executes the command using execve.
 * - Exits with appropriate error codes on failure.
 */
void	exec_cmd(t_pipex *pipex, int input_fd, int output_fd, char **cmd)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(pipex, cmd[0], pipex->envp);
	if (!cmd_path)
		free_resources_on_error(pipex, "Invalid command", 127);
	if (dup2(input_fd, STDIN_FILENO) < 0 || dup2(output_fd, STDOUT_FILENO) < 0)
		free_resources_on_error(pipex, "Error redirecting input/output", 1);
	close(pipex->pipefd[1]);
	execve(cmd_path, cmd, pipex->envp);
	if (errno == EACCES)
		free_resources_on_error(pipex, "Error executing command", 126);
	else
		free_resources_on_error(pipex, "Error executing command", 127);
}
