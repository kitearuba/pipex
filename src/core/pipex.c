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

/* ************************************************************************** */
/*                          Argument Validation                               */
/* ************************************************************************** */

/**
 * validate_args - Validates command-line arguments.
 * @argc: Argument count passed to the program.
 * Exits the program if the number of arguments is incorrect or if the PATH
 * environment variable is missing.
 */
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

/* ************************************************************************** */
/*                           Process Management                               */
/* ************************************************************************** */

/**
 * wait_for_processes - Waits for child processes to finish.
 * @pid1: Process ID of the first child process.
 * @pid2: Process ID of the second child process.
 * @status2: Pointer to the exit status of the second process.
 */
static void	wait_for_processes(pid_t pid1, pid_t pid2, int *status2)
{
	int	status1;

	status1 = 0;
	waitpid(pid1, &status1, 0);
	waitpid(pid2, status2, 0);
}

/* ************************************************************************** */
/*                                Main Program                                */
/* ************************************************************************** */

/**
 * main - Entry point for the pipex program.
 * @argc: Argument count.
 * @argv: Argument vector containing input/output files and commands.
 * @envp: Environment variables.
 * Initializes resources, handles command execution, and cleans up.
 * Returns:
 * - Exit status of the second command on success.
 * - 1 on failure.
 */
int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	/* Initialize pipex structure */
	pipex.infile = -1;
	pipex.outfile = -1;
	pipex.pipefd[0] = -1;
	pipex.pipefd[1] = -1;
	pipex.status2 = 0;
	/* Validate arguments and environment */
	validate_args(argc);
	/* Initialize, open files, and create pipe */
	init_pipex(&pipex, argv, envp);
	open_files(argv, &pipex);
	create_pipe(pipex.pipefd, &pipex);
	/* Handle command execution */
	pipex.pid1 = handle_fork(&pipex, pipex.cmd1, 1);
	pipex.pid2 = handle_fork(&pipex, pipex.cmd2, 2);
	/* Close pipe ends and wait for processes */
	close(pipex.pipefd[0]);
	close(pipex.pipefd[1]);
	wait_for_processes(pipex.pid1, pipex.pid2, &pipex.status2);
	/* Clean up and exit */
	free_pipex(&pipex);
	if (WIFEXITED(pipex.status2))
		return (WEXITSTATUS(pipex.status2));
	return (1);
}
