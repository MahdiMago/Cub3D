/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:36:20 by mamagoma          #+#    #+#             */
/*   Updated: 2026/01/03 11:56:26 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	load_one_tex(t_env *env, const char *path, t_tex *t)
{
	if (!path)
		return (0);
	t->img = mlx_xpm_file_to_image(env->mlx, (char *)path, &t->w, &t->h);
	if (!t->img)
		return (0);
	t->addr = mlx_get_data_addr(t->img, &t->bpp, &t->ll, &t->endian);
	return (t->addr != NULL);
}

const char	*get_texture_path(const char *parsed_path, const char *default_path)
{
	if (parsed_path)
		return (parsed_path);
	return (default_path);
}

int	load_textures(t_env *env)
{
	const char	*p_n;
	const char	*p_s;
	const char	*p_e;
	const char	*p_w;

	p_n = get_texture_path(env->parsing.tex_path[TEX_NORTH],
			"./textures/north.xpm");
	p_s = get_texture_path(env->parsing.tex_path[TEX_SOUTH],
			"./textures/south.xpm");
	p_e = get_texture_path(env->parsing.tex_path[TEX_EAST],
			"./textures/east.xpm");
	p_w = get_texture_path(env->parsing.tex_path[TEX_WEST],
			"./textures/west.xpm");
	if (!load_one_tex(env, p_n, &env->parsing.tex[TEX_NORTH]))
		return (0);
	if (!load_one_tex(env, p_s, &env->parsing.tex[TEX_SOUTH]))
		return (0);
	if (!load_one_tex(env, p_e, &env->parsing.tex[TEX_EAST]))
		return (0);
	if (!load_one_tex(env, p_w, &env->parsing.tex[TEX_WEST]))
		return (0);
	return (1);
}

void	destroy_textures(t_env *env)
{
	int	i;

	if (!env || !env->mlx)
		return ;
	i = 0;
	while (i < TEX_MAX)
	{
		if (env->parsing.tex[i].img)
		{
			mlx_destroy_image(env->mlx, env->parsing.tex[i].img);
			env->parsing.tex[i].img = NULL;
			env->parsing.tex[i].addr = NULL;
			env->parsing.tex[i].bpp = 0;
			env->parsing.tex[i].ll = 0;
			env->parsing.tex[i].endian = 0;
			env->parsing.tex[i].w = 0;
			env->parsing.tex[i].h = 0;
		}
		++i;
	}
}
