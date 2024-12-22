/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:18:38 by chrrodri          #+#    #+#             */
/*   Updated: 2024/12/22 16:02:58 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

/* ************************************************************************** */
/*                          Argument Validation                               */
/* ************************************************************************** */

/**
 * validate_args - Validates command-line arguments.
 * @argc: Argument count passed to the program.
 * @envp: Environment variables.
 * Exits the program if the number of arguments is incorrect or if the PATH
 * environment variable is missing.
 */
static void	validate_args(int argc, char **envp)
{
	if (argc != 5)
	{
		ft_printf_fd(STDERR_FILENO,
			"pipex: usage: ./pipex infile cmd1 cmd2 outfile\n");
		exit (1);
	}
	if (!get_path_from_env(envp))
	{
		ft_printf_fd(STDERR_FILENO,
			"pipex: Error: PATH not found in environment variables\n");
		exit (1);
	}
}

/* ************************************************************************** */
/*                        Process and Command Execution                       */
/* ************************************************************************** */

/**
 * execute_commands - Executes the given commands.
 * @pipex: Pointer to the pipex structure.
 *
 * Creates two child processes to handle the commands, closes pipe ends, and
 * waits for the processes to finish.
 */
static void	execute_commands(t_pipex *pipex)
{
	pipex->pid1 =handle_fork(pipex, 1);
	pipex->pid2 =handle_fork(pipex, 2);
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	waitpid(pipex->pid1, NULL, 0);
	waitpid(pipex->pid2, &pipex->status2, 0);
}

/**
 * initialize_pipex - Initializes resources for the pipex program.
 * @pipex: Pointer to the pipex structure.
 * @argv: Argument vector containing filenames and commands.
 * @envp: Environment variables.
 *
 * Handles initialization of resources such as command parsing, file handling,
 * and pipe creation.
 */
static void	initialize_pipex(t_pipex *pipex, char **argv, char **envp)
{
	init_pipex(pipex, argv, envp);
	open_files(argv, pipex);
	create_pipe(pipex->pipefd, pipex);
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

	ft_memset(&pipex, -1, sizeof(t_pipex));
	validate_args(argc, envp);
	initialize_pipex(&pipex, argv, envp);
	execute_commands(&pipex);
	free_pipex(&pipex);
	if (WIFEXITED(pipex.status2))
		return (WEXITSTATUS(pipex.status2));
	return (1);
}
