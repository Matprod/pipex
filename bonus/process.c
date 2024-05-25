/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoisin <mvoisin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:53:00 by mvoisin           #+#    #+#             */
/*   Updated: 2024/05/25 13:48:21 by mvoisin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void first_process(char **argv, char **envp, t_pipex *pipex)
{
	printf("test\n");
	if (close(STDIN_FILENO) == -1)
		error("Error : close");
	dup2(pipex->filein, STDIN_FILENO);
	dup2(pipex->pipe_fd[1], STDOUT_FILENO); //protect
	close(pipex->pipe_fd[0]);
	close(pipex->filein); //protect
	printf("argv de fp = %s\n", argv[2]);
	execute(argv[2], envp);
}

void child_process(int i, char **argv, char **envp, t_pipex *pipex)
{
	printf("child process erreur \n");
	dup2(pipex->pipe_fd[0], STDIN_FILENO); //protect
	dup2(pipex->pipe_fd[1], STDOUT_FILENO); //protect
	close(pipex->pipe_fd[1]); //protect
	execute(argv[i], envp);
}

void last_process(char *argv, char **envp, t_pipex *pipex)
{
	close_files(pipex, 0);
	dup2(pipex->pipe_fd[0], STDIN_FILENO);
	close(pipex->pipe_fd[1]); //protect
	printf("argv de lp = %s\n", argv);
	execute(argv, envp);
}