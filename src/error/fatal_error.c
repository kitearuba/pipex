/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatal_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:37:27 by chrrodri          #+#    #+#             */
/*   Updated: 2024/12/08 19:25:43 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

/**
 * Prints an error message and terminates the program.
 *
 * @msg: Main error message to display.
 * @detail: Additional detail about the error (optional).
 * @use_errno: If set to 1, appends the system error message (strerror).
 *
 * Description:
 * - Prints a formatted error message to standard output.
 * - Includes optional details and a system error message if requested.
 * - Terminates the program with an error exit code (1).
 */

void	fatal_error(const char *msg, const char *detail, int use_errno)
{
	if (msg)
		ft_printf_fd(STDERR_FILENO, "pipex: %s", msg);
	if (detail)
		ft_printf_fd(STDERR_FILENO, " '%s'", detail);
	if (use_errno)
		ft_printf_fd(STDERR_FILENO, ": %s", strerror(errno));
	ft_printf_fd(STDERR_FILENO, "\n");
	exit (1);
}
