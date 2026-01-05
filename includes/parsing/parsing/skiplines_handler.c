/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skiplines_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:28:51 by mamagoma          #+#    #+#             */
/*   Updated: 2026/01/05 14:20:35 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**skip_lines(char **map_copy, char *argv, t_map *map)
{
	int	i;
	int	j;
	int	c;

	i = 0;
	j = 0;
	c = 0;
	map->before_map = malloc(sizeof(char *) * 7);
	while (map_copy[i])
	{
		map->trim_str = ft_strtrim(map_copy[i], " \t\n\v\f\r");
		if (map->trim_str && map->trim_str[0] != '\0')
		{
			map->before_map[j] = map_copy[i];
			j++;
			c++;
		}
		if (condition(c, map) == 1)
			break ;
		i++;
		free(map->trim_str);
	}
	map->before_map[j] = NULL;
	after_copy(map, i, argv, map_copy);
	return (map->after_map);
}

void	after_copy(t_map *map, int i, char *argv, char **map_copy)
{
	int	j;

	map->after_map = malloc(sizeof(char *) * ((count_lines(argv) - 6) + 1));
	j = 0;
	i++;
	while (map_copy[i])
	{
		map->after_map[j] = map_copy[i];
		j++;
		i++;
	}
	map->after_map[j] = NULL;
}
