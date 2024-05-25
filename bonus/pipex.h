/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoisin <mvoisin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 05:50:47 by Matprod           #+#    #+#             */
/*   Updated: 2024/05/25 13:44:20 by mvoisin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "get_next_line_bonus.h"

typedef struct s_pipex
{
	int 	filein;
	int 	fileout;
	int 	pipe_fd[2];
	int		nb_cmd;
	int		is_here_doc;
	pid_t 	pid;
}	t_pipex;

/* BONUS functions */
void	here_doc(char **argv, t_pipex *pipex) ;
void open_files(t_pipex *pipex, char **argv);
void close_files(t_pipex *pipex, int i);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	error(char *str);
char	*find_path(char *cmd, char **envp);
char	*ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
void	execute(char *argv, char **envp);
size_t	ft_strlen(char *s);
char	**ft_split(char const *s, char c);

void first_process(char **argv, char **envp, t_pipex *pipex);
void child_process(int i, char **argv, char **envp, t_pipex *pipex);
void last_process(char *argv, char **envp, t_pipex *pipex);

#endif