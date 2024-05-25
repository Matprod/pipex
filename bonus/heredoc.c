/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoisin <mvoisin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:16:04 by mvoisin           #+#    #+#             */
/*   Updated: 2024/05/25 12:51:00 by mvoisin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc_put_in(char **av, t_pipex *pipex)
{
	char	*line;

	close(pipex->pipe_fd[0]);
	while (1)
	{
		line = get_next_line(0);
		if (ft_strncmp(line, av[2], ft_strlen(av[2])) == 0)
		{
			free(line);
			exit(0);
		}
		write(pipex->pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
}

void	here_doc(char **argv, t_pipex *pipex) 
{
	if (pipe(pipex->pipe_fd) == -1)
		exit(0);
	pipex->pid = fork();
	if (pipex->pid == -1)
		exit(0);
	if (!pipex->pid)
		here_doc_put_in(argv, pipex);
	else
	{
		close(pipex->pipe_fd[1]);
		dup2(pipex->pipe_fd[0], 0);
		wait(NULL);
	}
}