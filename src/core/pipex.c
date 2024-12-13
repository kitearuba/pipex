/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:18:38 by chrrodri          #+#    #+#             */
/*   Updated: 2024/12/08 19:32:53 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Initialize the pipex structure and perform required setup.
 * Handles initialization, file opening, and pipe creation.
 * Returns 0 on success or 1 on error, with appropriate error messages.
 */
static int	initialize_pipex(t_pipex *pipex, char **argv, char **envp)
{
	if (init_pipex(pipex, argv, envp))
	{
		ft_printf_fd(STDERR_FILENO, "pipex: error: failed to initialize pipex\n");
		free_pipex(pipex);
		return (1);
	}
	if (open_files(argv, pipex))
	{
		ft_printf_fd(STDERR_FILENO, "pipex: error: failed to open files\n");
		free_pipex(pipex);
		return (1);
	}
	if (create_pipe(pipex->pipefd))
	{
		ft_printf_fd(STDERR_FILENO, "pipex: error: failed to create pipe\n");
		free_pipex(pipex);
		return (1);
	}
	return (0);
}

/**
 * Main function of the Pipex program.
 * Takes 5 arguments: file1, cmd1, cmd2, and file2.
 * Initializes the t_pipex structure, opens files, creates pipes,
 * and handles process forks to execute commands.
 */
int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	pid1 = -1;
	pid2 = -1;
	if (argc != 5)
	{
		ft_printf_fd(STDERR_FILENO, "pipex: usage: ./pipex file1 cmd1 cmd2 file2\n");
		return (1);
	}
	if (initialize_pipex(&pipex, argv, envp))
		return (1);
	pid1 = handle_fork(&pipex, pipex.cmd1, 1);
	if (pid1 < 0)
	{
		free_pipex(&pipex);
		return (1);
	}
	pid2 = handle_fork(&pipex, pipex.cmd2, 2);
	if (pid2 < 0) {
		free_pipex(&pipex);
		return (1);
	}
	// Close pipe in parent process
	close(pipex.pipefd[0]);
	close(pipex.pipefd[1]);
	// Wait for both processes and exit with cmd2's status
	waitpid(pid1, NULL, 0); // Wait for cmd1
	waitpid(pid2, &status, 0); // Wait for cmd2 and get its status
	free_pipex(&pipex);
	if (WIFEXITED(status)) // Extract exit code if cmd2 exited normally
		return (WEXITSTATUS(status));
	return (1); // Default error code if cmd2 didn't exit normally
}

/**
* Main function of the Pipex program.
* Takes 5 arguments: file1, cmd1, cmd2, and file2.
* Initializes the t_pipex structure, opens files, creates pipes,
* and handles process forks to execute commands.

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
	{
		ft_printf_fd(STDERR_FILENO, "pipex: usage: ./pipex file1 cmd1 cmd2 file2\n");
		return (1);
	}
	if (init_pipex(&pipex, argv, envp)
		|| open_files(argv, &pipex)
		|| create_pipe(pipex.pipefd))
	{
		free_pipex(&pipex);
		return (1);
	}
	if (handle_fork(&pipex, pipex.cmd1, 1)
		|| handle_fork(&pipex, pipex.cmd2, 2))
	{
		free_pipex(&pipex);
		return (1);
	}
	free_pipex(&pipex);
	return (0);
}
*/