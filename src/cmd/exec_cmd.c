/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:50:31 by chrrodri          #+#    #+#             */
/*   Updated: 2024/12/16 15:06:58 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

/**
 * Executes a given command with redirected input/output.
 * @pipex: Pointer to the main pipex structure.
 * @input_fd: File descriptor for the command's input.
 * @output_fd: File descriptor for the command's output.
 * @cmd: Command and its arguments to execute.
 * Description:
 * - Resolves the command's absolute path using get_cmd_path.
 * - Redirects input/output using dup2.
 * - Executes the command using execve.
 * - Handles errors such as invalid commands or failed redirection.
 * Returns:
 * - Does not return on success; the process is replaced by execve.
 * - Cleans up resources and exits with appropriate codes on failure.
 */
int	exec_cmd(t_pipex *pipex, int input_fd, int output_fd, char **cmd)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(cmd[0]);
	if (!cmd_path)
	{
		close(pipex->pipefd[1]);
		free_resources_on_error(pipex, "Invalid command");
		exit(127);
	}
	if (dup2(input_fd, STDIN_FILENO) < 0 || dup2(output_fd, STDOUT_FILENO) < 0)
		cleanup_and_handle(cmd_path, cmd,
			"Error redirecting input/output", pipex);
	close(pipex->pipefd[1]);
	execve(cmd_path, cmd, pipex->envp);
	cleanup_and_handle(cmd_path, cmd, "Error executing command", NULL);
	if (errno == EACCES)
		exit(126);
	else
		exit(127);
}
