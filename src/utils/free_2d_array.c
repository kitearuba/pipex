/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2d_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:54:18 by chrrodri          #+#    #+#             */
/*   Updated: 2024/11/20 22:02:25 by chrrodri         ###   ########.fr       */
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
void	free_2d_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}
