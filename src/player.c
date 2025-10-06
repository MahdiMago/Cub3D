/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 01:49:43 by mamagoma          #+#    #+#             */
/*   Updated: 2025/10/05 01:57:06 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGH / 2;
	player->angle = PI / 2;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

int	keypress(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == D)
		player->key_right = true;
	if (keycode == LEFT)
		player->left_rotate = true;
	if (keycode == RIGHT)
		player->right_rotate = true;
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == LEFT)
		player->left_rotate = false;
	if (keycode == RIGHT)
		player->right_rotate = false;
	return (0);
}

void	try_move(t_player *player, float dx, float dy, t_env *env)
{
	float	new_x = player->x + dx;
	float	new_y = player->y + dy;

	if (!touch(new_x, player->y, env))
		player->x += dx;
	if (!touch(player->x, new_y, env))
		player->y += dy;
}

void	move_player(t_player *player)
{
	int		speed = 3;
	float	angle_speed = 0.03;
	float	cos_angle = cos(player->angle);
	float	sin_angle = sin(player->angle);

	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
	if (player->key_up)
		try_move(player, cos_angle * speed, sin_angle * speed, player->env);
	if (player->key_down)
		try_move(player, -cos_angle * speed, -sin_angle * speed, player->env);
	if (player->key_left)
		try_move(player, sin_angle * speed, -cos_angle * speed, player->env);
	if (player->key_right)
		try_move(player, -sin_angle * speed, cos_angle * speed, player->env);
}
