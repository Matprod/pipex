/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoisin <mvoisin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:23:49 by Matprod           #+#    #+#             */
/*   Updated: 2024/05/25 13:49:36 by mvoisin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_process(char **argv, char **envp, t_pipex *file)
{
	dup2(file->pipe_fd[1], STDOUT_FILENO);
	dup2(file->filein, STDIN_FILENO);
	close(file->pipe_fd[0]);
	execute(argv[2], envp);
}

void	second_process(char **argv, char **envp, t_pipex *file)
{
	dup2(file->pipe_fd[0], STDIN_FILENO);
	dup2(file->fileout, STDOUT_FILENO);
	close(file->pipe_fd[1]);
	execute(argv[3], envp);
}
void open_files(t_pipex *file, char **argv)
{
	file->filein = open(argv[1], O_RDONLY); //check
	if (file->filein == -1)
		error("Error : open filein");
	file->fileout = open(argv[4],  O_TRUNC | O_CREAT | O_RDWR, 0000644); //check
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

int		main(int argc, char **argv, char **envp)
{
	t_pipex	file;
	pid_t 	pid1;
	pid_t 	pid2;
	
	if (argc != 5)
		return (write(2, "Error: Bad arguments\n", 21));
	open_files(&file, argv);
	if (pipe(file.pipe_fd) == -1)
		error("Error : pipe");
	pid1 = fork();
	if (pid1 == -1)
		error("Error : fork");
	if (pid1 == 0)
		first_process(argv, envp, &file);
	pid2 = fork();
	if (pid2 == -1)
		error("Error : fork");
	if (pid2 == 0)
		second_process(argv, envp, &file);
	close_files(&file, 0);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	close_files(&file, 1);
	return (0);
}
