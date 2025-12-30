/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 17:39:04 by mamagoma          #+#    #+#             */
/*   Updated: 2025/10/19 17:55:48 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	set_player_angle(t_player *player, char dir)
{
	if (dir == 'N')
		player->angle = 3 * PI / 2;
	else if (dir == 'S')
		player->angle = PI / 2;
	else if (dir == 'E')
		player->angle = 0;
	else if (dir == 'W')
		player->angle = PI;
}

void	init_player_pos(t_env *env)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (env->parsing.map[y])
	{
		x = 0;
		while (env->parsing.map[y][x])
		{
			c = env->parsing.map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				env->player.x = (x + 0.5) * BLOCK;
				env->player.y = (y + 0.5) * BLOCK;
				set_player_angle(&env->player, c);
				return ;
			}
			x++;
		}
		y++;
	}
}
