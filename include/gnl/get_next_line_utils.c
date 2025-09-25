/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:21:18 by mamagoma          #+#    #+#             */
/*   Updated: 2024/11/22 21:05:47 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *str)
{
	int		i;
	char	*copy;

	i = 0;
	copy = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!copy)
		return (NULL);
	while (str[i])
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*rendu;

	i = 0;
	j = 0;
	rendu = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!rendu)
		return (NULL);
	while (s1[i])
	{
		rendu [i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		rendu[i++] = s2[j++];
	}
	rendu[i] = '\0';
	return (rendu);
}

char	*ft_substr(const char *str, int start, int len)
{
	int		i;
	int		len_str;
	char	*res;

	if (!str)
		return (NULL);
	i = 0;
	len_str = ft_strlen(str);
	if (len > len_str - start)
		len = len_str - start;
	if (len_str < start)
		len = 0;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (str[start] && i < len)
	{
		res[i++] = str[start++];
	}
	res[i] = '\0';
	return (res);
}

int	ft_strchr(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	if (str[i] == c)
		return ((char)str[i]);
	return (0);
}
