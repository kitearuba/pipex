/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:32:16 by chrrodri          #+#    #+#             */
/*   Updated: 2024/11/20 21:32:43 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	init_pipex(t_pipex *pipex, char **argv, char **envp)
{
	pipex->envp = envp;
	pipex->cmd1 = ft_split(argv[2], ' ');
	pipex->cmd2 = ft_split(argv[3], ' ');
	if (!pipex->cmd1 || !pipex->cmd2)
	{
		free_pipex(pipex);
		fatal_error("Error initializing pipex", NULL, 0);
		return (1);
	}
	return (0);
}
