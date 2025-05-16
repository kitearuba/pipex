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

#include "../../include/pipex_bonus.h"

static void	set_redirections(t_pipex *pipex, int i)
{
    if (i == 0)
    {
        dup2(pipex->infile, STDIN_FILENO);
        dup2(pipex->pipes[i][1], STDOUT_FILENO);
    }
    else if (i == pipex->cmd_count - 1)
    {
        dup2(pipex->pipes[i - 1][0], STDIN_FILENO);
        dup2(pipex->outfile, STDOUT_FILENO);
    }
    else
    {
        dup2(pipex->pipes[i - 1][0], STDIN_FILENO);
        dup2(pipex->pipes[i][1], STDOUT_FILENO);
    }
}

static void	close_all_pipes(t_pipex *pipex)
{
    int	i;

    i = 0;
    while (i < pipex->cmd_count - 1)
    {
        close(pipex->pipes[i][0]);
        close(pipex->pipes[i][1]);
        i++;
    }
}

void	handle_fork(t_pipex *pipex, int i)
{
    pid_t	pid;

    pid = fork();
    if (pid < 0)
        free_resources_on_error(pipex, "fork failed", 1);
    if (pid == 0)
    {
        close_all_pipes(pipex);
        set_redirections(pipex, i);
        if (pipex->here_doc && i == 0)
            close(pipex->infile);
        if (!pipex->here_doc && i == pipex->cmd_count - 1)
            close(pipex->outfile);
        exec_cmd(pipex, pipex->cmds[i]);
        exit(1);
    }
}
