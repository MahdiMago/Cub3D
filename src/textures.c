/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:36:20 by mamagoma          #+#    #+#             */
/*   Updated: 2026/01/04 21:36:26 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	load_one_tex(t_env *env, const char *path, t_tex *t)
{
	t->img = mlx_xpm_file_to_image(env->mlx, (char *)path, &t->w, &t->h);
	if (!t->img)
		return (0);
	t->addr = mlx_get_data_addr(t->img, &t->bpp, &t->ll, &t->endian);
	return (t->addr != NULL);
}

int	load_textures(t_env *env)
{
	if (!load_one_tex(env, env->map2->no_path, &env->tex[TEX_NORTH]))
		return (0);
	if (!load_one_tex(env, env->map2->so_path, &env->tex[TEX_SOUTH]))
		return (0);
	if (!load_one_tex(env, env->map2->we_path, &env->tex[TEX_WEST]))
		return (0);
	if (!load_one_tex(env, env->map2->ea_path, &env->tex[TEX_EAST]))
		return (0);
	return (1);
}

void	destroy_textures(t_env *env)
{
	int	i;

	i = 0;
	while (i < TEX_MAX)
	{
		if (env->tex[i].img)
			mlx_destroy_image(env->mlx, env->tex[i].img);
	}
}
