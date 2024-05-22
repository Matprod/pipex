/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoisin <mvoisin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 05:50:47 by Matprod           #+#    #+#             */
/*   Updated: 2024/05/22 15:51:23 by mvoisin          ###   ########.fr       */
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

/* BONUS functions */
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	error(void);
char	*find_path(char *cmd, char **envp);
char	*ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
void	execute(char *argv, char **envp);
size_t	ft_strlen(char *s);
char	**ft_split(char const *s, char c);

#endif