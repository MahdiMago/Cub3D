/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:25:30 by mamagoma          #+#    #+#             */
/*   Updated: 2026/01/05 20:29:05 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"

void	check_instructions(char **before_map)
{
	int		i;
	int		c;
	char	**split_str;

	i = 0;
	c = 0;
	doubles_check(before_map);
	while (before_map[i])
	{
		split_str = ft_split(before_map[i], 32);
		if (!ft_strcmp(split_str[0], "NO") || !ft_strcmp(split_str[0], "SO")
			|| !ft_strcmp(split_str[0], "EA") || !ft_strcmp(split_str[0], "WE")
			|| !ft_strcmp(split_str[0], "F") || !ft_strcmp(split_str[0], "C"))
			c++;
		free_map(split_str);
		i++;
	}
	if (c != 6)
	{
		ft_error("error: wrong map instructions\n", before_map);
		exit(1);
	}
}

void	free_maps(t_map *map)
{
	if (map->map_copy)
		free_map(map->map_copy);
	if (map->skip_map)
		free_map(map->skip_map);
	if (map->before_map)
		free_map(map->before_map);
	if (map->after_map)
		free_map(map->after_map);
	if (map->rectangular_map)
		free_map(map->rectangular_map);
	if (map->dummy_map)
		free_map(map->dummy_map);
	if (map->trim_map)
		free_map(map->trim_map);
}

void	check_doubles(char **map_copy)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	check2(map_copy);
	while (map_copy[i])
	{
		if (ft_strchr(map_copy[i], 'S') || ft_strchr(map_copy[i], 'E')
			|| ft_strchr(map_copy[i], 'N') || ft_strchr(map_copy[i], 'W'))
			c++;
		if (c > 1)
		{
			ft_error("error: player has two positions\n", map_copy);
			exit(1);
		}
		i++;
	}
}

void	find_position(char **map_copy)
{
	int	i;
	int	j;
	int	x;
	int	y;

	x = -1;
	y = -1;
	i = 0;
	while (map_copy[i])
	{
		j = 0;
		while (map_copy[i][j])
		{
			if (map_copy[i][j] == 'N' || map_copy[i][j] == 'E'
				|| map_copy[i][j] == 'S' || map_copy[i][j] == 'W')
			{
				x = j;
				y = i;
			}
			j++;
		}
		i++;
	}
	error(x, y);
}
