/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_gestion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoisin <mvoisin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:22:57 by mvoisin           #+#    #+#             */
/*   Updated: 2024/05/25 15:39:58 by mvoisin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_files(t_pipex *file, char **argv, int argc)
{
	file->filein = open(argv[1], O_RDONLY);
	if (file->filein == -1)
		error("Error : open filein");
	file->fileout = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (file->fileout == -1)
		error("Error : open fileout");
}

/*close files: PIPE = 0 | FILES = 1 | ALL = 2*/
void	close_files(t_pipex *file, int i)
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
	if (i == 2)
	{
		close(file->pipe_fd[0]);
		close(file->pipe_fd[1]);
		close(file->filein);
		close(file->fileout);
	}
}
