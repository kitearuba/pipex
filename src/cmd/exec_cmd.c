/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:50:31 by chrrodri          #+#    #+#             */
/*   Updated: 2024/12/08 23:04:47 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

/**
 * Executes a given command with redirected input/output.
 *
 * @pipex: Pointer to the main pipex structure.
 * @input_fd: File descriptor for the command's input.
 * @output_fd: File descriptor for the command's output.
 * @cmd: Command and its arguments to execute.
 *
 * Description:
 * - Resolves the command's absolute path using get_cmd_path.
 * - Redirects input/output using dup2.
 * - Executes the command using execve.
 * - Handles errors such as invalid commands or failed redirection.
 *
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
        ft_printf_fd(STDERR_FILENO, "pipex: %s: command not found\n", cmd[0]);
        close(pipex->pipefd[1]); // Explicitly close pipefd[1]
        free_2d_array(cmd);
        exit(127);
    }
    if (dup2(input_fd, STDIN_FILENO) < 0)
    {
        close(input_fd); // Explicitly close input_fd
        cleanup_and_handle(cmd_path, cmd, "Error redirecting input", pipex);
    }
    if (dup2(output_fd, STDOUT_FILENO) < 0)
    {
        close(output_fd); // Explicitly close output_fd
        cleanup_and_handle(cmd_path, cmd, "Error redirecting output", pipex);
    }
    close(pipex->pipefd[1]); // Close pipefd[1] after redirection
    execve(cmd_path, cmd, pipex->envp);
    cleanup_and_handle(cmd_path, cmd, "Error executing command", NULL);
    exit(1);
}
