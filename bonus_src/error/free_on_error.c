/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_on_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:31:36 by chrrodri          #+#    #+#             */
/*   Updated: 2024/12/28 23:00:05 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

void	free_resources_on_error(t_pipex *pipex, const char *error_message,
    int exit_code)
{
    int	i;
    int	saved_errno;

    saved_errno = errno;
    if (pipex->cmds)
    {
        i = 0;
        while (i < pipex->cmd_count)
        {
            if (pipex->cmds[i])
                free_2d_array(pipex->cmds[i]);
            i++;
        }
        free(pipex->cmds);
    }
    if (pipex->pipes)
    {
        i = 0;
        while (i < pipex->cmd_count - 1)
        {
            if (pipex->pipes[i])
                free(pipex->pipes[i]);
            i++;
        }
        free(pipex->pipes);
    }
    if (pipex->infile >= 0)
        close(pipex->infile);
    if (pipex->outfile >= 0)
        close(pipex->outfile);
    if (error_message && *error_message)
        ft_printf_fd(STDERR_FILENO, "pipex: %s\n", error_message);
    else if (saved_errno)
        ft_printf_fd(STDERR_FILENO, "pipex: %s\n", strerror(saved_errno));
    exit(exit_code);
}
