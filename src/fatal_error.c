/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatal_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:37:27 by chrrodri          #+#    #+#             */
/*   Updated: 2024/11/20 21:40:38 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void    fatal_error(const char *msg, const char *detail, int use_errno)
{
    if (msg)
        ft_printf("Error: %s", msg);
    if (detail)
        ft_printf(" '%s'", detail);
    if (use_errno)
        ft_printf(": %s", strerror(errno));
    ft_printf("\n");
    exit(EXIT_FAILURE);
}