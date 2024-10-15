//
// Created by christian on 14/10/24.
//

#ifndef PIPEX_PIPEX_H
#define PIPEX_PIPEX_H

#include <unistd.h>  // For pipe(), fork(), dup2(), execve()
#include <fcntl.h>   // For open(), O_RDONLY, O_WRONLY
#include <stdlib.h>  // For malloc(), free(), exit()
#include <stdio.h>   // For perror()
#include <sys/wait.h> // For waitpid()
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
int     create_pipe(int *pipefd);
char    *get_cmd_path(char *cmd);
int     exec_cmd(t_pipex *pipex, int input_fd, int output_fd, char **cmd);
int     handle_fork(t_pipex *pipex, char **cmd, int index);

#endif //PIPEX_PIPEX_H
