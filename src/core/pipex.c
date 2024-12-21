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

static void	validate_args(int argc)
{
	if (argc != 5)
	{
		ft_printf_fd(STDERR_FILENO,
		"pipex: usage: ./pipex infile cmd1 cmd2 outfile\n");
		exit (1);
	}
	if (!getenv("PATH")) {
		ft_printf_fd(STDERR_FILENO,
		"pipex: Error: PATH not found in environment variables\n");
		exit (1);
	}
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

	pipex.infile = -1;
	pipex.outfile = -1;
	pipex.pipefd[0] = -1;
	pipex.pipefd[1] = -1;
	pipex.status2 = 0;
	validate_args(argc);
	init_pipex(&pipex, argv, envp);
	open_files(argv, &pipex);
	create_pipe(pipex.pipefd, &pipex);
	pipex.pid1 = handle_fork(&pipex, pipex.cmd1, 1);
	pipex.pid2 = handle_fork(&pipex, pipex.cmd2, 2);
	close(pipex.pipefd[0]);
	close(pipex.pipefd[1]);
	wait_for_processes(pipex.pid1, pipex.pid2, &pipex.status2);
	free_pipex(&pipex);
	if (WIFEXITED(pipex.status2))
		return (WEXITSTATUS(pipex.status2));
	return (1);
}
