/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:37:27 by chrrodri          #+#    #+#             */
/*   Updated: 2024/12/08 19:27:47 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

/**
 * Handles pipe-related errors and prints an error message.
 *
 * @str: Error message to display.
 * @pipefd: Pipe file descriptors to close if valid.
 *
 * Description:
 * - Closes both ends of the pipe (if valid) to free resources.
 * - Delegates error reporting and program termination to `fatal_error`.
 * - Returns 1 for consistency, though the program exits in `fatal_error`.
 */
int	error_handle(char *str, int *pipefd)
{
	if (pipefd)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	fatal_error(str, NULL, 1);
	return (1);
}
