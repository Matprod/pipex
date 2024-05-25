/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoisin <mvoisin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:23:49 by Matprod           #+#    #+#             */
/*   Updated: 2024/05/25 17:31:59 by mvoisin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(char *argv, char **envp, t_pipex *pipex)
{
	if (pipe(pipex->pipe_fd) == -1)
		error("Error : pipe child");
	
	pipex->nb_pids++;
	pipex->pids[pipex->nb_pids] = fork();
	if (pipex->pids[pipex->nb_pids] == -1)
		error("Error : fork child");
	if (pipex->pids == 0)
	{
		close(pipex->pipe_fd[0]);
		dup2(pipex->pipe_fd[1], STDOUT_FILENO);
		execute(argv, envp);
	}
	else
	{
		close(pipex->pipe_fd[1]);
		dup2(pipex->pipe_fd[0], STDIN_FILENO);
		close_files(pipex, 0);
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
	t_pipex		pipex;

	pipex.nb_pids = 0;
	pipex.nb_cmd = argc -3;
	pipex.pids = malloc(sizeof(pid_t)*pipex.nb_cmd);
	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
		{
			i = 3;
			pipex.fileout = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
			here_doc(argv);
		}
		else
		{
			i = 2;
			open_files(&pipex, argv, argc);
			dup2(pipex.filein, STDIN_FILENO);
		}
		while (i < pipex.nb_cmd)
		{
			child_process(argv[i++], envp, &pipex);
		}
		while(i < pipex.nb_pids)
		{
			waitpid(pipex.pids[pipex.nb_pids], NULL, 0);
		}
		dup2(pipex.fileout, STDOUT_FILENO);
		execute(argv[argc - 2], envp);
	}
    close_files(&pipex, 1);
    return (0);
}
