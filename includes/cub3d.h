
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

# define DEBUG 0

#define COLOR_NORTH 0xFF0000 // rouge
#define COLOR_SOUTH 0x00FF00 // vert
#define COLOR_EAST  0x0000FF // bleu
#define COLOR_WEST  0xFFFF00 // jaune

# include "mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

typedef struct s_env t_env;

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

	t_env	*env;
	
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

//player.c :
void	init_player(t_player *player);
int		keypress(int keycode, t_player *player);
void	move_player(t_player *player);
int	key_release(int keycode, t_player *player);

//main.c :
bool	touch(float px, float py, t_env *env);

#endif
