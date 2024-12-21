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

/* ************************************************************************** */
/*                              File Handling                                 */
/* ************************************************************************** */

/**
 * open_files - Opens the input and output files for the pipex program.
 * @argv: Argument vector containing input/output file paths.
 * @pipex: Pointer to the pipex structure to store file descriptors.
 * Description:
 * - Opens the input file (read-only).
 * - Creates/truncates the output file with appropriate permissions.
 * - Exits with error if any file operation fails.
 */
void	open_files(char **argv, t_pipex *pipex)
{
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
		free_resources_on_error(pipex, "Unable to open input file", 1);
	pipex->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile < 0)
		free_resources_on_error(pipex, "Unable to open output file", 1);
}
