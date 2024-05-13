/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Matprod <matprod42@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 05:50:47 by Matprod           #+#    #+#             */
/*   Updated: 2024/05/13 06:38:58 by Matprod          ###   ########.fr       */
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


/* Mandatory functions */
void	error(void);
char	*find_path(char *cmd, char **envp);
char	*ft_strjoin(char *s1, char const *s2);
//int		get_next_line(char **line);
void	execute(char *argv, char **envp);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);



#endif