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

#include "../../include/pipex_bonus.h"

void	exec_cmd(t_pipex *pipex, char **cmd)
{
    char	*cmd_path;

    cmd_path = get_cmd_path(pipex, cmd[0]);
    if (!cmd_path)
        free_resources_on_error(pipex, "Command not found", 127);
    execve(cmd_path, cmd, pipex->envp);
    if (errno == EACCES)
        free_resources_on_error(pipex, "Permission denied", 126);
    else
        free_resources_on_error(pipex, strerror(errno), 127);
}

