//
// Created by christian on 14/10/24.
//

#ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h>     // For pipe(), fork(), dup2(), execve()
#include <fcntl.h>      // For open(), O_RDONLY, O_WRONLY
#include <stdlib.h>     // For malloc(), free(), exit()
#include <stdio.h>      // For perror()
#include <sys/wait.h>   // For waitpid()
#include <errno.h>      // To access errno
#include <string.h>     // For strerror
#include "../libft/include/libft.h"

typedef struct s_pipex
{
    int     file1;
    int     file2;
    int     pipefd[2];
    char    **cmd1;
    char    **cmd2;
    char    **envp;
}               t_pipex;

void    free_2d_array(char **array);
int     error_handle(char *str, int *pipefd);
int     open_files(char **argv, t_pipex *pipex);
void    free_resources_on_error(t_pipex *pipex, const char *error_message);
int     create_pipe(int *pipefd);
char    *get_cmd_path(char *cmd);
int     exec_cmd(t_pipex *pipex, int input_fd, int output_fd, char **cmd);
int     handle_fork(t_pipex *pipex, char **cmd, int index);
int	    init_pipex(t_pipex *pipex, char **argv, char **envp);
void	free_pipex(t_pipex *pipex);
void	free_resources_on_error(t_pipex *pipex, const char *error_message);
void    fatal_error(const char *msg, const char *detail, int use_errno);
char    **get_path_dirs(char **cmd_path);

#endif //PIPEX_H