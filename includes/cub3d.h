
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

// # define PI 3.14159265359
# define PI 3.14159265358979323846

# define DEBUG 0

#define COLOR_NORTH 0xFF0000 // rouge
#define COLOR_SOUTH 0x00FF00 // vert
#define COLOR_EAST  0x0000FF // bleu
#define COLOR_WEST  0xFFFF00 // jaune

# include <string.h>
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

//main.c :
void	put_pixel(int x, int y, int color, t_env *env);
void	clear_image(t_env *env);
void	draw_square(int x, int y, int size, int color, t_env *env);
char **get_map(void);
void	draw_map(t_env *env);
void	init_env(t_env *env);
bool	touch(float px, float py, t_env *env);
// int	line_color(float px, float py, t_env *env);
float	distance(float x, float y);
float	fixed_dist(float x1, float y1, float x2, float y2, t_env *env);
void	draw_line(t_player *player, t_env *env, float start_x, int i);
int	draw_loop(t_env *env);

//player.c :
void	init_player(t_player *player);
int		keypress(int keycode, t_player *player);
void	move_player(t_player *player);
int	key_release(int keycode, t_player *player);

<<<<<<< HEAD
//main.c :
int		draw_loop(t_env *env);
void	put_pixel(int x, int y, int color, t_env *env);
void	clear_image(t_env *env);
void	draw_square(int x, int y, int size, int color, t_env *env);
char	**get_map(void);
void	draw_map(t_env *env);
void	init_env(t_env *env);
bool	touch(float px, float py, t_env *env);
int		line_color(float px, float py, t_env *env);
float	distance(float x, float y);
float	fixed_dist(float x1, float y1, float x2, float y2, t_env *env);
void	draw_line(t_player *player, t_env *env, float start_x, int i);
=======
>>>>>>> 563f04d (save)

#endif
