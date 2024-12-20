/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:18:38 by chrrodri          #+#    #+#             */
/*   Updated: 2024/12/16 16:39:09 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"
/**
 * Initialize the pipex structure and perform required setup.
 * Handles all errors internally and exits the program if an error occurs.
 */
static void	initialize_pipex(t_pipex *pipex, char **argv, char **envp)
{
	if (init_pipex(pipex, argv, envp))
		free_resources_on_error(pipex, "failed to initialize pipex");
	if (open_files(argv, pipex))
		free_resources_on_error(pipex, "failed to open files");
	if (create_pipe(pipex->pipefd))
		free_resources_on_error(pipex, "failed to create pipe");
}

static void	wait_for_processes(pid_t pid1, pid_t pid2, int *status2)
{
	int	status1;

	status1 = 0;
	waitpid(pid1, &status1, 0);
	waitpid(pid2, status2, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	pid_t	pid1;
	pid_t	pid2;
	int		status2;

	pid1 = -1;
	pid2 = -1;
	status2 = 0;
	if (argc != 5)
	{
		ft_printf_fd(STDERR_FILENO,
		"pipex: usage: ./pipex infile cmd1 cmd2 outfile\n");
		return (1);
	}
	initialize_pipex(&pipex, argv, envp);
	pid1 = handle_fork(&pipex, pipex.cmd1, 1);
	pid2 = handle_fork(&pipex, pipex.cmd2, 2);
	close(pipex.pipefd[0]);
	close(pipex.pipefd[1]);
	wait_for_processes(pid1, pid2, &status2);
	free_pipex(&pipex);
	if (WIFEXITED(status2))
		return (WEXITSTATUS(status2));
	return (1);
}
