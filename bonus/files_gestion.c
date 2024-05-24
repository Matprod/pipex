/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_gestion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoisin <mvoisin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:10:29 by mvoisin           #+#    #+#             */
/*   Updated: 2024/05/24 18:15:22 by mvoisin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void open_files(t_pipex *file, char **argv)
{
	file->filein = open(argv[1], O_RDONLY);
	if (file->filein == -1)
		error("Error : open filein");
	file->fileout = open(argv[4],  O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (file->fileout == -1)
		error("Error : open fileout");
}

void close_files(t_pipex *file, int i)
{
	if (i == 0)
	{
		close(file->pipe_fd[0]);
		close(file->pipe_fd[1]);
	}
	if (i == 1)
	{
		close(file->filein);
		close(file->fileout);
	}
}