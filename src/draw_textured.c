/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textured.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:30:29 by mamagoma          #+#    #+#             */
/*   Updated: 2025/10/19 16:28:08 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static unsigned int	texel(const t_tex *t, int x, int y)
{
	char	*p;

	p = t->addr + y * t->ll + x * (t->bpp >> 3);
	return (*(unsigned int *)p);
}

static void	put_px_img(t_env *env, int x, int y, unsigned int c)
{
	char	*p;

	if ((unsigned)x >= WIDTH || (unsigned)y >= HEIGH)
		return ;
	p = env->data + y * env->size_line + x * (env->bpp >> 3);
	*(unsigned int *)p = c;
}

static const t_tex	*pick_texture(const t_hit *h, const t_env *env)
{
	if (h->side == 0)
	{
		if (h->stepx > 0)
			return (&env->tex[TEX_WEST]);
		else
			return (&env->tex[TEX_EAST]);
	}
	else if (h->stepy > 0)
		return (&env->tex[TEX_NORTH]);
	return (&env->tex[TEX_SOUTH]);
}

static void	drawing_loop(t_drawvars vars, const t_hit *h,
				t_tex_vars t_var, t_env *env)
{
	int				y;
	unsigned int	c;

	y = vars.y0;
	while (++y <= vars.y1)
	{
		t_var.tex_y = (int)t_var.tex_pos;
		if ((unsigned)t_var.tex_y >= (unsigned)t_var.tex_h)
			t_var.tex_y = t_var.tex_h - 1;
		t_var.tex_pos += t_var.step;
		c = texel(t_var.tex, t_var.tex_x, t_var.tex_y);
		if (h->side == 1)
			c = ((c >> 1) & 0x7F7F7F) | (c & 0xFF000000);
		put_px_img(env, t_var.col_x, y, c);
	}
}

void	draw_textured_column(int col_x, t_drawvars vars,
					const t_hit *h, t_env *env)
{
	t_tex_vars	t_var;

	t_var.tex = pick_texture(h, env);
	t_var.tex_w = t_var.tex->w;
	t_var.tex_h = t_var.tex->h;
	t_var.col_x = col_x;
	if (h->side == 0)
		t_var.wall_x = fmod(h->y, (double)BLOCK) / (double)BLOCK;
	else
		t_var.wall_x = fmod(h->x, (double)BLOCK) / (double)BLOCK;
	t_var.tex_x = (int)(t_var.wall_x * (double)t_var.tex_w);
	if ((h->side == 0 && h->stepx > 0) || (h->side == 1 && h->stepy < 0))
		t_var.tex_x = t_var.tex_w - t_var.tex_x - 1;
	t_var.step = (double)t_var.tex_h / (double)vars.col_h;
	t_var.tex_pos = ((double)vars.orig_y0 - (double)HEIGH
			/ 2.0 + (double)vars.col_h / 2.0) * t_var.step;
	t_var.tex_pos += (double)(vars.y0 - vars.orig_y0)*t_var.step;
	drawing_loop(vars, h, t_var, env);
}
