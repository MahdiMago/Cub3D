/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:47:35 by mamagoma          #+#    #+#             */
/*   Updated: 2025/10/19 17:55:33 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pixel(int x, int y, int color, t_env *env)
{
	int	index;

	if (x >= WIDTH || y >= HEIGH || x < 0 || y < 0)
		return ;
	index = y * env->size_line + x * env->bpp / 8;
	env->data[index] = color & 0xFF;
	env->data[index + 1] = (color >> 8) & 0xFF;
	env->data[index + 2] = (color >> 16) & 0xFF;
}

void	clear_image(t_env *env)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGH)
	{
		x = 0;
		while (x < WIDTH)
			put_pixel(x++, y, 0, env);
		y++;
	}
}

void	draw_square(int x, int y, int color, t_env *env)
{
	int	i;

	i = 0;
	while (i < BLOCK)
		put_pixel(x + i, y, 0x00FF00, env);
	i = 0;
	while (i < BLOCK)
		put_pixel(x + BLOCK, y + i, 0x00FF00, env);
	i = 0;
	while (i < BLOCK)
		put_pixel(x, y + i, 0x00FF00, env);
	i = 0;
	while (i < BLOCK)
		put_pixel(x + i, y + BLOCK, 0x00FF00, env);
}

char	**get_map(void)
{
	int		i;
	char	**map;

	map = malloc(sizeof(char *) * 11);
	i = 0;
	map[i++] = "111111111111111";
	map[i++] = "100000000000001";
	map[i++] = "100000000000001";
	map[i++] = "100000200000001";
	map[i++] = "100000000000001";
	map[i++] = "1000000300000011111111111";
	map[i++] = "10000400W0000011111100001";
	map[i++] = "1000000000000011111000001";
	map[i++] = "1000000000000000000011111";
	map[i++] = "111111111111111111111";
	map[i] = NULL;
	return (map);
}

void	draw_map(t_env *env)
{
	int		y;
	int		x;
	char	**map;

	y = 0;
	map = env->parsing.map;
	if (!map)
		return ;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, 0XFF00, env);
			x++;
		}
		y++;
	}
}
