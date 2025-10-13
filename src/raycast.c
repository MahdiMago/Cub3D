/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:40:31 by mamagoma          #+#    #+#             */
/*   Updated: 2025/10/13 17:24:23 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_inverse_dirs(t_rayinfo *r)
{
	if (fabsf(r->dirx) < 1e-8f)
	{
		if (r->dirx >= 0)
			r->inv_dirx = 1e8f;
		else
			r->inv_dirx = -1e8f;
	}
	else
		r->inv_dirx = 1.0f / r->dirx;
	if (fabsf(r->diry) < 1e-8f)
	{
		if (r->diry >= 0)
			r->inv_diry = 1e8f;
		else
			r->inv_diry = -1e8f;
	}
	else
		r->inv_diry = 1.0f / r->diry;
}

void	perform_dda(t_env *env, t_rayinfo *r)
{
	while (1)
	{
		if (r->sidex < r->sidey)
		{
			r->sidex += r->deltax;
			r->mapx += r->stepx;
			r->side = 0;
		}
		else
		{
			r->sidey += r->deltay;
			r->mapy += r->stepy;
			r->side = 1;
		}
		if (is_solid_cell(env, r->mapx, r->mapy))
			break ;
	}
}

void	init_hit(t_compute_vars	vars, t_rayinfo *r, t_hit *hit)
{
	hit->dist = vars.dist;
	hit->x = vars.ix;
	hit->y = vars.iy;
	hit->side = r->side;
	hit->stepx = r->stepx;
	hit->stepy = r->stepy;
}

void	compute_hit(const t_player *p, t_rayinfo *r, t_hit *hit)
{
	t_compute_vars	vars;

	if (r->side == 0)
		vars.dist = fabsf((r->mapx - r->cellx + (1 - r->stepx) * 0.5f)
				* r->inv_dirx);
	else
		vars.dist = fabsf((r->mapy - r->celly + (1 - r->stepy) * 0.5f)
				* r->inv_diry);
	vars.dist *= BLOCK;
	vars.ix = p->x + r->dirx * vars.dist;
	vars.iy = p->y + r->diry * vars.dist;
	if (r->side == 0)
	{
		if (r->stepx > 0)
			hit->color = COLOR_WEST;
		else
			hit->color = COLOR_EAST;
	}
	else if (r->stepy > 0)
		hit->color = COLOR_NORTH;
	else
		hit->color = COLOR_SOUTH;
	init_hit(vars, r, hit);
}

void	cast_ray(const t_player *p, float ray_ang, t_env *env, t_hit *hit)
{
	t_rayinfo	r;

	init_ray_dir(ray_ang, &r);
	init_ray_grid(p, &r);
	init_ray_steps(&r);
	perform_dda(env, &r);
	compute_hit(p, &r, hit);
}
