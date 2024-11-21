/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:50:31 by chrrodri          #+#    #+#             */
/*   Updated: 2024/11/20 21:51:36 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	exec_cmd(t_pipex *pipex, int input_fd, int output_fd, char **cmd)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(cmd[0]);
	if (cmd_path == NULL)
	{
		fatal_error("Command not found", cmd[0], 0);
		free_2d_array(cmd);
		return (1);
	}
	if (dup2(input_fd, STDIN_FILENO) < 0 || dup2(output_fd, STDOUT_FILENO) < 0)
	{
		free(cmd_path);
		free_2d_array(cmd);
		return (error_handle("Error with dup2", pipex->pipefd));
	}
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	execve(cmd_path, cmd, pipex->envp);
	fatal_error("Error executing command", cmd[0], 1); // Handles execve errors
	free(cmd_path);
	free_2d_array(cmd);
	return (1);
}