/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:00:00 by chrrodri          #+#    #+#             */
/*   Updated: 2024/12/22 16:09:05 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include "../libft/include/libft.h"

typedef struct s_pipex
{
    int		infile;
    int		outfile;
    int		**pipes;
    int		cmd_count;
    char	***cmds;
    char	**envp;
    int		here_doc;
}	t_pipex;

/* core */
void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp);
void	create_pipes(t_pipex *pipex);
void	handle_fork(t_pipex *pipex, int i);
void	open_files(char **argv, t_pipex *pipex, int argc);
void	exec_cmd(t_pipex *pipex, char **cmd);

/* error */
void	free_resources_on_error(t_pipex *pipex, const char *error_message,
    int exit_code);

/* utils */
void	free_pipex(t_pipex *pipex);
char    *get_cmd_path(t_pipex *pipex, char *cmd);
char	*get_path_from_env(char **envp);
void	free_2d_array(char **array);

#endif
