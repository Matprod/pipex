/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Matprod <matprod42@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:23:49 by Matprod           #+#    #+#             */
/*   Updated: 2024/05/23 20:52:33 by Matprod          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_process(char *av[], char *envp[], int filein)
{
	pid_t pid1;
	int		pipe_fd[2];
	
	if (pipe(pipe_fd) == -1)
		error("pipe");
	pid1 = fork();
	if (pid1 == -1)
		error("fork");
	if (pid1 == 0)
	{
		if (filein == -1)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			error("infile");
		}
		dup2(pipe_fd[1], STDOUT_FILENO);
		execute(av[2], envp);
	}
	else
	{
		if (waitpid(pid1, NULL, 0) == -1)
			error("waitpid function");
	}
}

void	child_process(char *argv, char **envp)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		error("Error : pipe");
	pid = fork();
	if (pid == -1)
		error("Error : fork");
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		execute(argv, envp);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		waitpid(pid, NULL, WNOHANG);
	}
}

void	here_doc_put_in(char **av, int *pipe_fd)
{
	char	*line;

	close(pipe_fd[0]);
	while (1)
	{
		line = get_next_line(0);
		if (ft_strncmp(line, av[2], ft_strlen(av[2])) == 0)
		{
			free(line);
			exit(0);
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
}

void	here_doc(char **argv)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
		here_doc_put_in(argv, pipe_fd);
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		wait(NULL);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int			i;
	int			filein;
	int			fileout;

	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
		{
			i = 3;
			fileout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
			here_doc(argv);
		}
		else
		{
			i = 2;
			filein = open(argv[1], O_RDONLY, 0777);
			fileout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			dup2(filein, STDIN_FILENO);
		}
		while (i < argc -2)
			child_process(argv[i++], envp);
		dup2(fileout, STDOUT_FILENO);
		execute(argv[argc - 2], envp);
	}
	return (0);
}
