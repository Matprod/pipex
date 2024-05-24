/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoisin <mvoisin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:23:49 by Matprod           #+#    #+#             */
/*   Updated: 2024/05/24 19:47:03 by mvoisin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void first_process(char **argv, char **envp, t_pipex *file)
{
	if (pipe(file->pipe_fd) == -1)
			error("Error : pipe");
		file->pid = fork();
	if (file->pid == -1)
		error("Error : fork");
	if (close(STDIN_FILENO) == -1)
		error("Error : close");
	dup2(file->pipe_fd[1], STDOUT_FILENO);
	dup2(file->filein, STDIN_FILENO); //protect
	close(file->pipe_fd[0]); //protect
	execute(argv[2], envp);
}

void child_process(char *argv, char **envp, t_pipex *file)
{
	if (pipe(file->pipe_fd) == -1)
		error("Error : pipe");
	file->pid = fork();
	if (file->pid == -1)
		error("Error : fork");
	dup2(file->pipe_fd[0], STDIN_FILENO); //protect
	dup2(file->pipe_fd[1], STDOUT_FILENO); //protect
	close(file->pipe_fd[1]); //protect
	execute(argv, envp);
}

void last_process(char *argv, char **envp, t_pipex *file)
{
	if (pipe(file->pipe_fd) == -1)
		error("Error : pipe");
	file->pid = fork();
	if (file->pid == -1)
		error("Error : fork");
	if (close(STDOUT_FILENO) == -1)
		error("Error : close");
	dup2(file->pipe_fd[0], STDIN_FILENO);
	dup2(file->fileout, STDOUT_FILENO); //protect
	close(file->pipe_fd[1]); //protect
	execute(argv, envp);
}

int	main(int argc, char **argv, char **envp)
{
	int			i;
	t_pipex		file;

	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
		{
			i = 3;
			file.fileout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
			here_doc(argv, &file);
		}
		else
		{
			i = 3;
			open_files(&file, argv);
			first_process(argv, envp ,&file);
		}
		while (i < argc -2)
		{
			int pid = fork();
			//printf("test\n");
			if (pid == 0);
				child_process(argv[i++], envp, &file);
			waitpid(pid, NULL, 0);
		}
		last_process(argv[argc - 2], envp, &file);
		i = 3;
		close_files(&file, 0);
		close_files(&file, 1);
	}
	return (0);
}

/*

void	first_exec(t_list *cmd_lst, t_pipex *pipex)
{	
	if ((int)pipex->input_fd != -1)
	{
		if (dup2(pipex->input_fd, 0) == -1)
			fatal_error(pipex, E_DUP2);
	}
	else
		if (close(0) == -1)
			fatal_error(pipex, E_CLOSE);
	if (dup2(((t_cmd *)cmd_lst->content)->pipe[1], 1) == -1)
		fatal_error(pipex, E_DUP2);
	if (close(((t_cmd *)cmd_lst->content)->pipe[0]) == -1)
		fatal_error(pipex, E_CLOSE);
	if (close(pipex->input_fd) == -1)
		fatal_error(pipex, E_CLOSE);
	exec_cmd(((t_cmd *)cmd_lst->content), pipex);
}


Use the output of the previous pipe as standard input for the command and \ 
send the result into a new pipe.


void	middle_exec(t_list *cmd_lst, t_pipex *pipex)
{
	if (dup2(((t_cmd *)cmd_lst->previous->content)->pipe[0], 0) == -1)
		fatal_error(pipex, E_DUP2);
	if (dup2(((t_cmd *)cmd_lst->content)->pipe[1], 1) == -1)
		fatal_error(pipex, E_DUP2);
	if (close(((t_cmd *)cmd_lst->content)->pipe[1]) == -1)
		fatal_error(pipex, E_CLOSE);
	if (close(((t_cmd *)cmd_lst->previous->content)->pipe[0]) == -1)
		fatal_error(pipex, E_CLOSE);
	exec_cmd(((t_cmd *)cmd_lst->content), pipex);
}

Use the output of the previous pipe as standard input for the command and \ 
send the result into in output file.


void	last_exec(t_list *cmd_lst, t_pipex *pipex)
{
	if (close(((t_cmd *)cmd_lst->content)->pipe[1]) == -1)
		fatal_error(pipex, E_CLOSE);
	if (close(((t_cmd *)cmd_lst->content)->pipe[0]) == -1)
		fatal_error(pipex, E_CLOSE);
	if (dup2(((t_cmd *)cmd_lst->previous->content)->pipe[0], 0) == -1)
		fatal_error(pipex, E_DUP2);
	if (pipex->output_fd < 0)
	{
		if (dup2(0, 1) == -1)
			fatal_error(pipex, E_DUP2);
	}
	else
		if (dup2(pipex->output_fd, 1) == -1)
			fatal_error(pipex, E_DUP2);
	if (close(((t_cmd *)cmd_lst->previous->content)->pipe[0]) == -1)
		fatal_error(pipex, E_CLOSE);
	exec_cmd(((t_cmd *)cmd_lst->content), pipex);
}

Run the command if it is executable, otherwise, show error.


void	exec_cmd(t_cmd *cmd, t_pipex *pipex)
{
	char	**env;

	env = pipex->env;
	if (cmd->path_args[0] == NULL && pipex->is_error == 0)
		fatal_error(pipex, E_CMD);
	if (access(cmd->path_args[0], X_OK) == 0)
		if (execve(cmd->path_args[0], cmd->path_args, env) == -1)
			fatal_error(pipex, E_EXECVE);
}
*/