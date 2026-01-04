/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:28:32 by mamagoma          #+#    #+#             */
/*   Updated: 2026/01/04 21:35:51 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"

void	doubles_check(char **before_map)
{
	t_map	map;
	int		i;
	char	**split;

	map = (t_map){0};
	i = 0;
	while (before_map[i])
	{
		split = ft_split(before_map[i], ' ');
		if (!ft_strcmp(split[0], "NO"))
			map.no++;
		if (!ft_strcmp(split[0], "SO"))
			map.so++;
		if (!ft_strcmp(split[0], "EA"))
			map.ea++;
		if (!ft_strcmp(split[0], "WE"))
			map.we++;
		free_map(split);
		i++;
	}
	if (map.no > 1 || map.so > 1 || map.ea > 1 || map.we > 1)
	{
		ft_error("error: coordinates not found\n", before_map);
		exit(1);
	}
}

void	check2(char **map)
{
	int	i;
	int	j;
	int	c;

	i = 0;
	c = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
				|| map[i][j] == 'E')
				c++;
			j++;
		}
		i++;
	}
	if (c > 1)
	{
		ft_error("error: player has two positions", map);
		exit(1);
	}
}

int	condition(int c, t_map *map)
{
	if (c == 6)
	{
		free(map->trim_str);
		return (1);
	}
	return (0);
}

int	cal_h(char **map)
{
	int	i;
	int	j;
	int	h;

	h = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
			{
				h++;
				break ;
			}
			j++;
		}
		i++;
	}
	return (h);
}

unsigned long	convert_rgb(char *str)
{
	char			**rgb;
	int				r;
	int				g;
	int				b;
	unsigned long	color;

	rgb = ft_split(str, ',');
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	color = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	free_map(rgb);
	return (color);
}
