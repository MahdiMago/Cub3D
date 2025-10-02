/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 03:50:31 by mamagoma          #+#    #+#             */
/*   Updated: 2025/10/02 03:40:16 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 1280
# define HEIGH 720
# define BLOCK 64

# define W 119
# define S 115
# define A 97
# define D 100
# define LEFT 65361
# define RIGHT 65363

# define PI 3.14159265359

# include "mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

typedef struct	s_player
{
	float x;
	float y;
	float angle;

	bool key_up;
	bool key_down;
	bool key_left;
	bool key_right;

	bool	left_rotate;
	bool	right_rotate;
}	t_player;

typedef struct s_env
{
	void	*mlx;
	void	*win;
	void	*img;

	char	*data;
	int	bpp;
	int	size_line;
	int	endian;
	t_player	player;

	char	**map;
}	t_env;

void	init_player(t_player *player);
int		keypress(int keycode, t_player *player);
void	move_player(t_player *player);
int	key_release(int keycode, t_player *player);

#endif
