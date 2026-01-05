/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 16:50:31 by mamagoma          #+#    #+#             */
/*   Updated: 2026/01/05 20:34:35 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	free_map_arrays(t_map *map)
{
	if (map->map_copy)
		free_string_array(map->map_copy);
	if (map->trim_map)
		free_string_array(map->trim_map);
	if (map->no_path)
		free(map->no_path);
	if (map->so_path)
		free(map->so_path);
	if (map->we_path)
		free(map->we_path);
	if (map->ea_path)
		free(map->ea_path);
	if (map->before_map)
	{
		free(map->before_map);
		map->before_map = NULL;
	}
	free_extention(map);
}

void	free_map_end(t_map *map)
{
	if (!map)
		return ;
	free_map_arrays(map);
	free(map);
}

static void	free_env_resources(t_env *env)
{
	int	i;

	i = 0;
	if (env->map2)
		free_map_end(env->map2);
	while (i < TEX_MAX)
	{
		if (env->tex[i].img)
			mlx_destroy_image(env->mlx, env->tex[i].img);
		i++;
	}
	if (env->img)
		mlx_destroy_image(env->mlx, env->img);
}

int	close_window(t_env *env)
{
	if (!env)
		exit(0);
	free_env_resources(env);
	if (env->win)
		mlx_destroy_window(env->mlx, env->win);
	if (env->mlx)
	{
		mlx_destroy_display(env->mlx);
		if (env->mlx)
			free(env->mlx);
	}
	exit(0);
}
