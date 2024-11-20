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

#include "../include/pipex.h"

void	free_pipex(t_pipex *pipex)
{
	if (pipex->cmd1)
	{
		free_2d_array(pipex->cmd1);
		pipex->cmd1 = NULL;
	}
	if (pipex->cmd2)
	{
		free_2d_array(pipex->cmd2);
		pipex->cmd2 = NULL;
	}
}
