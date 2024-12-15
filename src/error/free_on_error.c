/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_on_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:31:36 by chrrodri          #+#    #+#             */
/*   Updated: 2024/12/15 22:38:06 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void free_resources_on_error(t_pipex *pipex, const char *error_message)
{
    if (pipex->file1 >= 0)
        close(pipex->file1);
    if (pipex->file2 >= 0)
        close(pipex->file2);
    if (pipex->cmd1)
	{
        free_2d_array(pipex->cmd1);
        pipex->cmd1 = NULL;
	}
    if (pipex->cmd2)
	{
        free_2d_array(pipex->cmd2);
        pipex->cmd2 = NULL;
	}
    if (error_message)
        ft_printf_fd(STDERR_FILENO, "%s\n", error_message);   
    exit (1); // Properly aligned outside the if block
}

