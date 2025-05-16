/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:19:17 by chrrodri          #+#    #+#             */
/*   Updated: 2024/12/08 19:43:47 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

static void	open_here_doc(t_pipex *pipex, char *limiter)
{
    char	*line;
    int		fd[2];
    size_t	limiter_len;

    if (pipe(fd) < 0)
        free_resources_on_error(pipex, "pipe failed", 1);
    limiter_len = ft_strlen(limiter);
    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(1, "heredoc> ", 9);
        line = get_next_line(STDIN_FILENO);
        if (!line)
            break ;
        if (ft_strncmp(line, limiter, limiter_len) == 0
            && line[limiter_len] == '\n')
        {
            free(line);
            break ;
        }
        write(fd[1], line, ft_strlen(line));
        free(line);
    }
    close(fd[1]);
    pipex->infile = fd[0];
}

void	open_files(char **argv, t_pipex *pipex, int argc)
{
    if (pipex->here_doc)
    {
        open_here_doc(pipex, argv[2]);
        pipex->outfile = open(argv[argc - 1],
                O_WRONLY | O_CREAT | O_APPEND, 0644);
    }
    else
    {
        pipex->infile = open(argv[1], O_RDONLY);
        pipex->outfile = open(argv[argc - 1],
                O_WRONLY | O_CREAT | O_TRUNC, 0644);
    }
    if (pipex->infile < 0 || pipex->outfile < 0)
        free_resources_on_error(pipex, "open failed", 1);
}
