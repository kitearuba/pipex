/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:18:38 by chrrodri          #+#    #+#             */
/*   Updated: 2024/11/20 21:33:08 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
	{
		ft_printf("Usage: ./pipex file1 cmd1 cmd2 file2\n");
		return (1);
	}
	if (init_pipex(&pipex, argv, envp) || open_files(argv, &pipex) \
			|| create_pipe(pipex.pipefd))
	{
		free_pipex(&pipex);
		return (1);
	}
	if (handle_fork(&pipex, pipex.cmd1, 1) \
			|| handle_fork(&pipex, pipex.cmd2, 2))
	{
		free_pipex(&pipex);
		return (1);
	}
	free_pipex(&pipex);
	return (0);
}
