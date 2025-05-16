/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:31:36 by chrrodri          #+#    #+#             */
/*   Updated: 2024/11/20 21:31:45 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

void	free_pipex(t_pipex *pipex)
{
    int	i;

    if (pipex->cmds)
    {
        i = 0;
        while (i < pipex->cmd_count)
        {
            if (pipex->cmds[i])
                free_2d_array(pipex->cmds[i]);
            i++;
        }
        free(pipex->cmds);
    }
    if (pipex->pipes)
    {
        i = 0;
        while (i < pipex->cmd_count - 1)
        {
            free(pipex->pipes[i]);
            i++;
        }
        free(pipex->pipes);
    }
}
