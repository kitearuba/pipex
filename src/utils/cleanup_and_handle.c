/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_and_handle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:50:31 by chrrodri          #+#    #+#             */
/*   Updated: 2024/11/21 21:19:50 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

int	cleanup_and_handle(char *cmd_path, char **cmd, char *error_msg, \
		t_pipex *pipex)
{
	if (cmd_path)
		free(cmd_path);
	if (cmd)
		free_2d_array(cmd);
	if (pipex)
		error_handle(error_msg, pipex->pipefd);
	else
		fatal_error(error_msg, NULL, 1);
	return (1);
}
