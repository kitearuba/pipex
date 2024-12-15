/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:18:38 by chrrodri          #+#    #+#             */
/*   Updated: 2024/12/15 20:16:45 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

/*
 * Initializes the pipex structure, opens files, and creates pipes.
 * Returns 0 on success or 1 on error.
 */
static int	initialize_pipex(t_pipex *pipex, char **argv, char **envp)
{
	if (init_pipex(pipex, argv, envp))
	{
		ft_printf_fd(STDERR_FILENO,
			"pipex: error: failed to initialize pipex\n");
		free_pipex(pipex);
		return (1);
	}
	if (open_files(argv, pipex))
	{
		ft_printf_fd(STDERR_FILENO,
			"pipex: error: failed to open files\n");
		free_pipex(pipex);
		return (1);
	}
	if (create_pipe(pipex->pipefd))
	{
		ft_printf_fd(STDERR_FILENO,
			"pipex: error: failed to create pipe\n");
		free_pipex(pipex);
		return (1);
	}
	return (0);
}

/*
 * Main function of the Pipex program.
 * Takes 5 arguments: file1, cmd1, cmd2, and file2.
 */
int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
	{
		ft_printf_fd(STDERR_FILENO,
			"pipex: usage: ./pipex file1 cmd1 cmd2 file2\n");
		return (1);
	}
	if (initialize_pipex(&pipex, argv, envp))
		return (1);
	if (handle_fork(&pipex, pipex.cmd1, 1)
		|| handle_fork(&pipex, pipex.cmd2, 2))
	{
		ft_printf_fd(STDERR_FILENO,
			"pipex: error: failed to execute commands\n");
		free_pipex(&pipex);
		return (1);
	}
	free_pipex(&pipex);
	return (0);
}
