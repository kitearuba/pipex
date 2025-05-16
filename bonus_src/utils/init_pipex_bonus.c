/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:32:16 by chrrodri          #+#    #+#             */
/*   Updated: 2024/12/08 18:52:38 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

/* ************************************************************************** */
/*                           Initialization Function                          */
/* ************************************************************************** */

static int	count_cmds(int argc, int here_doc)
{
    if (here_doc)
        return (argc - 4);
    return (argc - 3);
}

static char	***allocate_cmds(int count)
{
    char	***cmds;
    int		i;

    cmds = (char ***)malloc(sizeof(char **) * (count + 1));
    if (!cmds)
        return (NULL);
    i = 0;
    while (i < count)
    {
        cmds[i] = NULL;
        i++;
    }
    cmds[i] = NULL;
    return (cmds);
}

void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
    int		i;
    int		offset;

    pipex->here_doc = 0;
    if (ft_strncmp(argv[1], "here_doc", 8) == 0)
        pipex->here_doc = 1;
    pipex->envp = envp;
    pipex->cmd_count = count_cmds(argc, pipex->here_doc);
    pipex->cmds = allocate_cmds(pipex->cmd_count);
    if (!pipex->cmds)
        free_resources_on_error(pipex, "Failed to allocate cmds", 1);
    i = 0;
    offset = 2 + pipex->here_doc;
    while (i < pipex->cmd_count)
    {
        pipex->cmds[i] = ft_split(argv[i + offset], ' ');
        if (!pipex->cmds[i])
            free_resources_on_error(pipex, "Failed to parse command", 1);
        i++;
    }
}
