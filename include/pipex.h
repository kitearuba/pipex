/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christian <christian@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:00:00 by christian         #+#    #+#             */
/*   Updated: 2024/10/14 10:00:00 by christian        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>     /* For pipe(), fork(), dup2(), execve() */
# include <fcntl.h>      /* For open(), O_RDONLY, O_WRONLY */
# include <stdlib.h>     /* For malloc(), free(), exit() */
# include <stdio.h>      /* For perror() */
# include <sys/wait.h>   /* For waitpid() */
# include <errno.h>      /* To access errno */
# include <string.h>     /* For strerror() */
# include "../libft/include/libft.h"

/* Struct Definition */
typedef struct s_pipex
{
	int		file1;
	int		file2;
	int		pipefd[2];
	char	**cmd1;
	char	**cmd2;
	char	**envp;
}	t_pipex;

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

#endif // PIPEX_H