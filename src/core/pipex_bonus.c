/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex _bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:18:38 by chrrodri          #+#    #+#             */
/*   Updated: 2024/12/16 16:39:09 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

static int	handle_errors(const char *msg, t_pipex *pipex)
{
	ft_printf_fd(STDERR_FILENO, "pipex:error:%s/n", msg);
	free_pipex(pipex);
	return (1);
}

/**
 * Initialize the pipex structure and perform required setup.
 * Returns 0 on success or 1 on error, with appropriate error messages.
 */
static int	initialize_pipex(t_pipex *pipex, char **argv, char **envp)
{
	if (init_pipex(pipex, argv, envp))
		return (handle_errors("failed to initialize pipex", pipex));
	if (open_files(argv, pipex))
		return (handle_errors("failed to open files", pipex));
	if (create_pipe(pipex->pipefd))
		return (handle_errors("failed to create pipe", pipex));
	return (0);
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
			"pipex: usage: ./pipex file1 cmd1 cmd2 file2\n");
		return (1);
	}
	if (initialize_pipex(&pipex, argv, envp))
		return (1);
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
