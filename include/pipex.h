/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:00:00 by chrrodri          #+#    #+#             */
/*   Updated: 2024/12/21 21:26:45 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* ************************************************************************** */
/*                               Dependencies                                 */
/* ************************************************************************** */

# include <unistd.h>     /* For pipe(), fork(), dup2(), execve() */
# include <fcntl.h>      /* For open(), O_RDONLY, O_WRONLY */
# include <stdlib.h>     /* For malloc(), free(), exit() */
//# include <stdio.h>      /* For perror() */
# include <sys/wait.h>   /* For waitpid() */
# include <errno.h>      /* To access errno */
# include <string.h>     /* For strerror() */
# include "../libft/include/libft.h" /* Custom libft library */

/* ************************************************************************** */
/*                               Macros                                       */
/* ************************************************************************** */

/**
 * PIPEX_PATH_MAX: Maximum length for a command path.
 * Set to 4096, which aligns with common system limits for path lengths.
 */
# define PIPEX_PATH_MAX 4096

/* ************************************************************************** */
/*                               Structures                                   */
/* ************************************************************************** */

/**
 * struct s_pipex - Holds resources for the pipex program.
 * @infile: Input file descriptor.
 * @outfile: Output file descriptor.
 * @pipefd: Array for pipe's read and write ends.
 * @cmd1: Arguments for the first command.
 * @cmd2: Arguments for the second command.
 * @envp: Environment variables passed to the program.
 * @pid1: Process ID of the first child.
 * @pid2: Process ID of the second child.
 * @status2: Status of the second process.
 */
typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		pipefd[2];
	char	**cmd1;
	char	**cmd2;
	char	**envp;
	pid_t	pid1;
	pid_t	pid2;
	int		status2;
}	t_pipex;

/* ************************************************************************** */
/*                          Function Prototypes                               */
/* ************************************************************************** */

/* Utility Functions */
void	free_2d_array(char **array);
void	free_pipex(t_pipex *pipex);
/* Initialization*/
void	init_pipex(t_pipex *pipex, char **argv, char **envp);

/* Error Handling */
void	free_resources_on_error(t_pipex *pipex, const char *error_message,
			int exit_code);

/* File Handling */
void	open_files(char **argv, t_pipex *pipex);
void	create_pipe(int *pipefd, t_pipex *pipex);

/* Command Handling */
char	*get_cmd_path(t_pipex *pipex, char *cmd);
void	exec_cmd(t_pipex *pipex, int input_fd, int output_fd, char **cmd);

/* Process Handling */
int		handle_fork(t_pipex *pipex, char **cmd, int index);

#endif /* PIPEX_H */
