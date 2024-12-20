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

#include "../../include/pipex.h"

/**
 * open_files - Opens input and output files for the pipex program.
 * Handles errors and stores file descriptors in the t_pipex structure.
 * NOTE:
 * In C, a leading 0 indicates an octal (base 8) number, where each digit ranges 
 * from 0 to 7. 0644 means:owner can read/write (6 = 110 in binary), group and 
 * otherscan read (4 = 100).Without the leading 0, the number would be treated 
 * as decimal, leading to incorrect interpretation.
*/
void	open_files(char **argv, t_pipex *pipex)
{
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
		free_resources_on_error(pipex, "Error: Unable to open input file");
	pipex->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile < 0)
		free_resources_on_error(pipex, "Error: Unable to open output file");
}
