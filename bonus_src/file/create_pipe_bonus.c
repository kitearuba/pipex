/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:34:32 by chrrodri          #+#    #+#             */
/*   Updated: 2024/11/20 21:36:05 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

/* ************************************************************************** */
/*                              Pipe Creation                                 */
/* ************************************************************************** */

static void	allocate_pipes(t_pipex *pipex)
{
    int	i;

    pipex->pipes = (int **)malloc(sizeof(int *) * (pipex->cmd_count - 1));
    if (!pipex->pipes)
        free_resources_on_error(pipex, "Pipe allocation failed", 1);
    i = 0;
    while (i < pipex->cmd_count - 1)
    {
        pipex->pipes[i] = (int *)malloc(sizeof(int) * 2);
        if (!pipex->pipes[i])
            free_resources_on_error(pipex, "Pipe malloc failed", 1);
        i++;
    }
}

void	create_pipes(t_pipex *pipex)
{
    int	i;

    allocate_pipes(pipex);
    i = 0;
    while (i < pipex->cmd_count - 1)
    {
        if (pipe(pipex->pipes[i]) == -1)
            free_resources_on_error(pipex, "Pipe creation failed", 1);
        i++;
    }
}
