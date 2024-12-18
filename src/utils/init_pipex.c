/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:32:16 by chrrodri          #+#    #+#             */
/*   Updated: 2024/12/08 18:52:38 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

/**
 * Initializes the pipex structure with environment variables and commands.
 * Parses command-line arguments into executable commands and handles errors.
 */
int	init_pipex(t_pipex *pipex, char **argv, char **envp)
{
	pipex->envp = envp;
	pipex->cmd1 = ft_split(argv[2], ' ');
	pipex->cmd2 = ft_split(argv[3], ' ');
	if (!pipex->cmd1)
	{
		free_pipex(pipex);
		fatal_error("Error parsing cmd1", argv[2], 0);
		return (1);
	}
	if (!pipex->cmd2)
	{
		free_pipex(pipex);
		fatal_error("Error parsing cmd2", argv[3], 0);
		return (1);
	}
	return (0);
}
