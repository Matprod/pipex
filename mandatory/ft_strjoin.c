/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Matprod <matprod42@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 06:23:40 by Matprod           #+#    #+#             */
/*   Updated: 2024/05/13 07:13:07 by Matprod          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*dest;
	size_t	i;
	size_t	destlen;

	i = 0;
	destlen = ft_strlen(s1) + ft_strlen(s2);
	dest = malloc(destlen + 1 * sizeof(char));
	if (!dest)
		return (NULL);
	while (*(s1 + i))
	{
		*(dest + i) = *(s1 + i);
		i++;
	}
	while (*s2)
	{
		*(dest + i) = *s2++;
		i++;
	}
	*(dest + i) = '\0';
	return (dest);
}
