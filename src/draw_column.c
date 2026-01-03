/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 11:22:53 by mamagoma          #+#    #+#             */
/*   Updated: 2026/01/03 11:23:56 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calculate_distance(t_hit *h, t_env *env)
{
	t_distvars	dis_vars;

	dis_vars.x1 = env->player.x;
	dis_vars.x2 = h->x;
	dis_vars.y1 = env->player.y;
	dis_vars.y2 = h->y;
	h->dist = fixed_dist(dis_vars, env);
}

void	calculate_column_params(t_drawvars *vars, t_hit *h, float fov)
{
	vars->proj_distance = (WIDTH * 0.5f) / tanf(fov * 0.5f);
	vars->col_h = (int)fmaxf(1.0f, (BLOCK * vars->proj_distance)
			/ fmaxf(h->dist, 1e-4f));
	vars->y0 = (HEIGH - vars->col_h) / 2;
	vars->y1 = vars->y0 + vars->col_h - 1;
	vars->orig_y0 = vars->y0;
	if (vars->y0 < 0)
		vars->y0 = 0;
	if (vars->y1 >= HEIGH)
		vars->y1 = HEIGH - 1;
}

void	draw_ceiling(int col_x, t_drawvars *vars, t_env *env)
{
	int	ceil_col;

	ceil_col = env->parsing.color_ceiling;
	if (ceil_col < 0)
		ceil_col = 0x202020;
	vars->y = 0;
	while (vars->y < vars->y0)
	{
		put_pixel(col_x, vars->y, ceil_col, env);
		vars->y++;
	}
}

void	draw_floor(int col_x, t_drawvars *vars, t_env *env)
{
	int	floor_col;

	floor_col = env->parsing.color_floor;
	if (floor_col < 0)
		floor_col = 0x404040;
	vars->y = vars->y1 + 1;
	while (vars->y < HEIGH)
	{
		put_pixel(col_x, vars->y, floor_col, env);
		vars->y++;
	}
}
