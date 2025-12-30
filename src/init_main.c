/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:42:52 by mamagoma          #+#    #+#             */
/*   Updated: 2025/10/19 17:45:06 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_ray_grid(const t_player *p, t_rayinfo *r)
{
	r->cellx = p->x / BLOCK;
	r->celly = p->y / BLOCK;
	r->mapx = (int)floorf(r->cellx);
	r->mapy = (int)floorf(r->celly);
}

void	init_ray_steps(t_rayinfo *r)
{
	set_inverse_dirs(r);
	r->deltax = fabsf(r->inv_dirx);
	r->deltay = fabsf(r->inv_diry);
	if (r->dirx < 0.0f)
		r->stepx = -1;
	else
		r->stepx = 1;
	if (r->diry < 0.0f)
		r->stepy = -1;
	else
		r->stepy = 1;
	if (r->stepx > 0)
		r->sidex = (floorf(r->cellx) + 1.0f - r->cellx) * r->deltax;
	else
		r->sidex = (r->cellx - floorf(r->cellx)) * r->deltax;
	if (r->stepy > 0)
		r->sidey = (floorf(r->celly) + 1.0f - r->celly) * r->deltay;
	else
		r->sidey = (r->celly - floorf(r->celly)) * r->deltay;
}

void	init_env(t_env *env, const char *map_path)
{
	env->parsing.map = NULL;
	env->player.env = env;
	/* parse provided map, fallback to built-in get_map() if parse fails */
	if (map_path && !parse_file(map_path, &env->parsing))
	{
		fprintf(stderr, "Warning: failed to parse %s, using built-in map\n", map_path);
		env->parsing.map = get_map();
	}
	else if (!map_path)
		env->parsing.map = get_map();
	init_player(&env->player);
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIDTH, HEIGH, "CUB3D");
	env->img = mlx_new_image(env->mlx, WIDTH, HEIGH);
	env->data = mlx_get_data_addr(env->img,
			&env->bpp, &env->size_line, &env->endian);
	if (!load_textures(env))
	{
		fprintf(stderr, "Error: failed to load textures\n");
		exit(EXIT_FAILURE);
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}
