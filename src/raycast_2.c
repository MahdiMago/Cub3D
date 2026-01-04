/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:24:00 by mamagoma          #+#    #+#             */
/*   Updated: 2025/10/19 17:56:57 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	touch(float px, float py, t_env *env)
{
	int		x;
	int		y;
	char	c;

	x = px / BLOCK;
	y = py / BLOCK;
	c = env->map[y][x];
	if (c != '0' && c != 'N' && c != 'E' && c != 'W' && c != 'S')
		return (true);
	return (false);
}

void	draw_loop_2(t_env *env, t_player *player, t_loop_vars vars)
{
	t_hit	h;

	cast_ray(player, vars.start + vars.i * vars.step, env, &h);
	draw_column(vars.i++, &h, env, vars.fov);
}

int	draw_loop(t_env *env)
{
	t_player	*player;
	t_loop_vars	vars;

	player = &env->player;
	move_player(player);
	clear_image(env);
	vars.fov = (float)PI / 3.0f;
	vars.start = player->angle - vars.fov * 0.5f;
	vars.step = vars.fov / (float)WIDTH;
	vars.i = 0;
	while (vars.i < WIDTH)
	{
		draw_loop_2(env, player, vars);
		vars.i++;
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (0);
}
