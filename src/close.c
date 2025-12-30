/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 16:50:31 by mamagoma          #+#    #+#             */
/*   Updated: 2025/10/19 17:27:27 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	free_env_resources(t_env *env)
{
	int	i;

	i = 0;
	if (env->parsing.map)
	{
		i = 0;
		while (env->parsing.map[i])
		{
			free(env->parsing.map[i]);
			i++;
		}
		free(env->parsing.map);
	}
	i = 0;
	while (i < TEX_MAX)
	{
		if (env->parsing.tex[i].img)
			mlx_destroy_image(env->mlx, env->parsing.tex[i].img);
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
