/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:00:00 by chrrodri          #+#    #+#             */
/*   Updated: 2024/12/15 19:30:47 by chrrodri         ###   ########.fr       */
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
# include <stdio.h>      /* For perror() */
//# include <sys/wait.h>   /* For waitpid() */
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
 * @file1: File descriptor for the input file.
 * @file2: File descriptor for the output file.
 * @pipefd: Array holding the read and write ends of the pipe.
 * @cmd1: Parsed arguments for the first command.
 * @cmd2: Parsed arguments for the second command.
 * @envp: Environment variables passed to the program.
 */
typedef struct s_pipex
{
	int		file1;		/* Input file descriptor */
	int		file2;		/* Output file descriptor */
	int		pipefd[2];	/* Pipe file descriptors */
	char	**cmd1;		/* Arguments for the first command */
	char	**cmd2;		/* Arguments for the second command */
	char	**envp;		/* Environment variables */
}	t_pipex;

/* ************************************************************************** */
/*                          Function Prototypes                               */
/* ************************************************************************** */

/* Utility Functions */
void	free_2d_array(char **array);
void	free_pipex(t_pipex *pipex);
void	free_resources_on_error(t_pipex *pipex, const char *error_message);
void	fatal_error(const char *msg, const char *detail, int use_errno);

/* Initialization and Cleanup */
int		init_pipex(t_pipex *pipex, char **argv, char **envp);
int		cleanup_and_handle(char *cmd_path, char **cmd, char *error_msg,
			t_pipex *pipex);

/* Error Handling */
int		error_handle(char *str, int *pipefd);

/* File Handling */
int		open_files(char **argv, t_pipex *pipex);
int		create_pipe(int *pipefd);

/* Command Handling */
char	*get_cmd_path(char *cmd);
char	**get_path_dirs(char **cmd_path);
int		exec_cmd(t_pipex *pipex, int input_fd, int output_fd, char **cmd);

/* Process Handling */
int		handle_fork(t_pipex *pipex, char **cmd, int index);

#endif /* PIPEX_H */
