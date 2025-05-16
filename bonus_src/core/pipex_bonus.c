/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:18:38 by chrrodri          #+#    #+#             */
/*   Updated: 2024/12/28 18:33:22 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"


static void	validate_args(int argc, char **argv, char **envp)
{
    if ((ft_strncmp(argv[1], "here_doc", 8) == 0 && argc < 6)
        || (ft_strncmp(argv[1], "here_doc", 8) != 0 && argc < 5))
    {
        ft_printf_fd(STDERR_FILENO,
            "Usage:\n"
            "  ./pipex infile cmd1 cmd2 [cmdN] outfile\n"
            "  ./pipex here_doc LIMITER cmd1 [cmdN] outfile\n");
        exit(1);
    }
	if (!get_path_from_env(envp))
	{
	    ft_printf_fd(STDERR_FILENO,
            "pipex: PATH not found in env\n");
	    exit(1);
	}
}

static void	execute_all_cmds(t_pipex *pipex)
{
    int	i;

    i = 0;
    while (i < pipex->cmd_count)
    {
        handle_fork(pipex, i);
        i++;
    }
    while (wait(NULL) > 0)
        ;
}

static void	initialize_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	init_pipex(pipex, argc, argv, envp);
	open_files(argv, pipex, argc);
	create_pipes(pipex);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	validate_args(argc, argv, envp);
	initialize_pipex(&pipex, argc, argv, envp);
	execute_all_cmds(&pipex);
	free_pipex(&pipex);
	return (0);
}
