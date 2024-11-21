/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:50:31 by chrrodri          #+#    #+#             */
/*   Updated: 2024/11/21 19:30:04 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

int	exec_cmd(t_pipex *pipex, int input_fd, int output_fd, char **cmd)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(cmd[0]);
	if (!cmd_path)
	{
		fatal_error("Command not found", cmd[0], 0);
		free_2d_array(cmd);
		return (1);
	}
	if (dup2(input_fd, STDIN_FILENO) < 0 || dup2(output_fd, STDOUT_FILENO) < 0)
		return (cleanup_and_handle(cmd_path, cmd, "Error with dup2", pipex));
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	execve(cmd_path, cmd, pipex->envp);
	cleanup_and_handle(cmd_path, cmd, "Error executing command", NULL);
	exit (1);
}
