/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:25:21 by mamagoma          #+#    #+#             */
/*   Updated: 2026/01/04 21:25:43 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"

static void	assign_texture_path(char **split_str, t_map *map)
{
	if (!ft_strcmp(split_str[0], "NO"))
		map->no_path = ft_strdup(split_str[1]);
	else if (!ft_strcmp(split_str[0], "SO"))
		map->so_path = ft_strdup(split_str[1]);
	else if (!ft_strcmp(split_str[0], "WE"))
		map->we_path = ft_strdup(split_str[1]);
	else if (!ft_strcmp(split_str[0], "EA"))
		map->ea_path = ft_strdup(split_str[1]);
}

static void	check_texture_path(char **split_str, t_map *map)
{
	if (open(split_str[1], O_RDONLY) == -1)
	{
		ft_error("error: path not found\n", map->before_map);
		free_map(split_str);
		exit(1);
	}
	if (check_xpm(split_str[1]) == 1)
	{
		ft_error("error: xpm only\n", map->before_map);
		exit(1);
	}
	assign_texture_path(split_str, map);
}

static void	process_line(char **split_str, t_map *map)
{
	if (!ft_strcmp(split_str[0], "NO") || !ft_strcmp(split_str[0], "SO")
		|| !ft_strcmp(split_str[0], "EA") || !ft_strcmp(split_str[0], "WE"))
		check_texture_path(split_str, map);
	else if (!ft_strcmp(split_str[0], "F"))
		map->floor_color = convert_rgb(split_str[1]);
	else if (!ft_strcmp(split_str[0], "C"))
		map->ceiling_color = convert_rgb(split_str[1]);
	check_c_f(split_str);
}

void	check_paths(t_map *map)
{
	char	**split_str;
	int		i;

	i = 0;
	while (map->before_map[i])
	{
		split_str = ft_split(map->before_map[i], 32);
		process_line(split_str, map);
		i++;
	}
}
