/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:31:36 by chrrodri          #+#    #+#             */
/*   Updated: 2024/11/20 21:31:45 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

/* ************************************************************************** */
/*                          2D Array Memory Cleanup                          */
/* ************************************************************************** */

/**
 * free_2d_array - Frees a dynamically allocated 2D array.
 * @arr: Pointer to the 2D array to free.
 * Description:
 * - Iterates through the array, freeing each individual element.
 * - Frees the array itself and sets its pointer to NULL.
 */
void	free_pipex(t_pipex *pipex)
{
	if (pipex->cmd1)
		free_2d_array(pipex->cmd1);
	if (pipex->cmd2)
		free_2d_array(pipex->cmd2);
}
