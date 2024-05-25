/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoisin <mvoisin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:23:49 by Matprod           #+#    #+#             */
/*   Updated: 2024/05/25 13:44:32 by mvoisin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_exec(int i, int argc, char **argv, char **envp, t_pipex *pipex)
{
	if (i == 0 && pipex->is_here_doc == 0)
		first_process(argv, envp, pipex);
	else if (i == 0 && pipex->is_here_doc == 1)
		here_doc(argv, pipex);
	else if (i != 0 && i == (pipex->nb_cmd - 1))
		last_process(argv[argc - 2], envp, pipex);
	else
		child_process(i, argv, envp, pipex);
}
void	first_exec_here_doc(char **argv, char **envp, t_pipex *pipex)
{
	if(dup2(pipex->pipe_fd[1], 1) == -1)
		error("Error : dup2");
	if (close((pipex->pipe_fd[0]) == -1))
		error("Error : close");
	execute(argv[2], envp);
}

void	set_nb_cmds(int argc, char **argv, t_pipex *pipex)
{
	if (!ft_strncmp(argv[2], "here_doc", 8))
		pipex->nb_cmd = argc - 4;
	else
		pipex->nb_cmd = argc - 3;
}
void	parent_wait(t_pipex *pipex)
{
	int		i;

	i = 0;
	while (i < pipex->nb_cmd)
	{
		waitpid(pipex->pid, NULL, 0);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	int			i;
	t_pipex		pipex;

	i = 0;
    pipex.pipe_fd[0] = 0;
    pipex.pipe_fd[1] = 0;
	pipex.filein = 0;
	pipex.fileout = 0;
	pipex.is_here_doc = 0;
	pipex.pid = 0;
	pipex.nb_cmd = 0;
	open_files(&pipex, argv);
	if (argc >= 5)
	{
		set_nb_cmds(argc, argv, &pipex);
		if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
		{
			i = 3;
			pipex.is_here_doc = 1;
			pipex.fileout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
			here_doc(argv, &pipex);
		}
		else
		{
			i = 0;
			while (i < pipex.nb_cmd)
			{
				if (pipe(pipex.pipe_fd) == -1)
					error("Error : pipe");;
				pipex.pid = fork();
				if (pipex.pid == -1)
					error("Error : fork");
				if (pipex.pid == 0)
				{
					child_exec(i, argc, argv, envp, &pipex);
				}
				else
				{
					waitpid(pipex.pid, NULL, 0);
					close_files(&pipex,2);
				}
				i++;
			}
			//parent_wait(&pipex);
		}
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