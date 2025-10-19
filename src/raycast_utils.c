/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:09:58 by mamagoma          #+#    #+#             */
/*   Updated: 2025/10/19 17:54:38 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	is_solid_cell(t_env *env, int mx, int my)
{
	char	c;

	if (my < 0 || !env->map[my])
		return (true);
	if (mx < 0 || mx >= (int)strlen(env->map[my]))
		return (true);
	c = env->map[my][mx];
	return (c != '0' && c != 'N' && c != 'E' && c != 'W' && c != 'S');
}

void	draw_column(int col_x, t_hit *h, t_env *env, float fov)
{
	t_drawvars	vars;
	t_distvars	dis_vars;

	dis_vars.x1 = env->player.x;
	dis_vars.x2 = h->x;
	dis_vars.y1 = env->player.y;
	dis_vars.y2 = h->y;
	h->dist = fixed_dist(dis_vars, env);
	vars.proj_distance = (WIDTH * 0.5f) / tanf(fov * 0.5f);
	vars.col_h = (int)fmaxf(1.0f, (BLOCK * vars.proj_distance)
			/ fmaxf(h->dist, 1e-4f));
	vars.y0 = (HEIGH - vars.col_h) / 2;
	vars.y1 = vars.y0 + vars.col_h - 1;
	vars.orig_y0 = vars.y0;
	if (vars.y0 < 0)
		vars.y0 = 0;
	if (vars.y1 >= HEIGH)
		vars.y1 = HEIGH - 1;
	vars.y = 0;
	while (vars.y < vars.y0)
		put_pixel(col_x, ++vars.y, 0x202020, env);
	vars.y = vars.y1;
	while (vars.y < HEIGH)
		put_pixel(col_x, ++vars.y, 0x404040, env);
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
