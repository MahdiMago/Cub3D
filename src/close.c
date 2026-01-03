/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 16:50:31 by mamagoma          #+#    #+#             */
/*   Updated: 2026/01/03 13:20:16 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static void	free_texture_paths(t_parsing *parsing)
{
	int	i;

	i = 0;
	while (i < TEX_MAX)
	{
		if (parsing->tex_path[i])
		{
			free(parsing->tex_path[i]);
			parsing->tex_path[i] = NULL;
		}
		i++;
	}
}

static void	free_texture_images(t_env *env)
{
	int	i;

	i = 0;
	while (i < TEX_MAX)
	{
		if (env->parsing.tex[i].img)
			mlx_destroy_image(env->mlx, env->parsing.tex[i].img);
		i++;
	}
}

static void	free_env_resources(t_env *env)
{
	free_map(env->parsing.map);
	free_texture_paths(&env->parsing);
	free_texture_images(env);
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
		free(env->mlx);
	}
	exit(0);
}
