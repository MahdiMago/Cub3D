/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:09:58 by mamagoma          #+#    #+#             */
/*   Updated: 2026/01/03 11:24:02 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	is_solid_cell(t_env *env, int mx, int my)
{
	char	c;

	if (my < 0 || !env->parsing.map[my])
		return (true);
	if (mx < 0 || mx >= (int)strlen(env->parsing.map[my]))
		return (true);
	c = env->parsing.map[my][mx];
	return (c != '0' && c != 'N' && c != 'E' && c != 'W' && c != 'S');
}

void	draw_column(int col_x, t_hit *h, t_env *env, float fov)
{
	t_drawvars	vars;

	calculate_distance(h, env);
	calculate_column_params(&vars, h, fov);
	draw_ceiling(col_x, &vars, env);
	draw_floor(col_x, &vars, env);
	draw_textured_column(col_x, vars, h, env);
}

float	distance(float x, float y)
{
	return (sqrt((x * x) + (y * y)));
}

float	fixed_dist(t_distvars vars, t_env *env)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fixed_dis;

	delta_x = vars.x2 - vars.x1;
	delta_y = vars.y2 - vars.y1;
	angle = atan2(delta_y, delta_x) - env->player.angle;
	fixed_dis = distance(delta_x, delta_y) * cos(angle);
	return (fixed_dis);
}

void	init_ray_dir(float ray_ang, t_rayinfo *r)
{
	r->dirx = cosf(ray_ang);
	r->diry = sinf(ray_ang);
}
