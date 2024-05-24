/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoisin <mvoisin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:23:49 by Matprod           #+#    #+#             */
/*   Updated: 2024/05/24 15:19:39 by mvoisin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_process(char **argv, char **envp, int *fd)
{
	int		filein;

	filein = open(argv[1], O_RDONLY, 0777);
	if (filein == -1)
		error("Error : open filein");
	dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(fd[0]);
	execute(argv[2], envp);
}

void	second_process(char **argv, char **envp, int *fd)
{
	int		fileout;

	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
		error("Error : open fileout");
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fd[1]);
	execute(argv[3], envp);
}
void open_files(t_pipex file, char **argv)
{
	file.filein = open(argv[1], O_RDONLY, 0777);
	file.fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
}

void close_files(t_pipex file, int i)
{
	if (i == 1)
	{
		close(file.filein);
		close(file.fileout);
	}
	if (i == 0)
	{
		close(file.pipe_fd[0]);
		close(file.pipe_fd[1]);
	}
}

int		main(int argc, char **argv, char **envp)
{
	t_pipex	file;
	pid_t 	pid1;
	pid_t 	pid2;
	
	if (!envp)
		return (EXIT_FAILURE);
	if (argc != 5)
		return (write(2, "Error: Bad arguments\n", 21));
	else
	{
		open_files(file, argv);
		if (pipe(file.pipe_fd) == -1)
			error("Error : pipe");
		pid1 = fork();
		if (pid1 == -1)
			error("Error : fork");
		if (pid1 == 0)
			first_process(argv, envp, file.pipe_fd);
		pid2 = fork();
		if (pid2 == -1)
			error("Error : fork");
		if (pid1 == 0)
			first_process(argv, envp, file.pipe_fd);
		if (pid2 == 0)
			second_process(argv, envp, file.pipe_fd);
		waitpid(pid1, NULL, 1);
		close_files(file, 1);
		close_files(file, 0);
		waitpid(pid1, NULL, 1);
	}
	return (0);
}
