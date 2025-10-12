
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

// --- Textures ---
typedef struct s_tex {
    void *img;
    char *addr;
    int   w;
    int   h;
    int   bpp;
    int   ll;     // line length (bytes)
    int   endian;
} t_tex;

typedef enum e_texid {
    TEX_NORTH = 0,
    TEX_SOUTH = 1,
    TEX_EAST  = 2,
    TEX_WEST  = 3,
    TEX_MAX   = 4
} t_texid;

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

typedef struct s_hit {
    float   dist;
    float   x;
    float   y;
    int     color;

    int     side;   // 0 = mur vertical (X), 1 = mur horizontal (Y)
    int     stepX;  // -1 ou 1 (sens de progression en X dans la DDA)
    int     stepY;  // -1 ou 1 (sens de progression en Y dans la DDA)
} t_hit;


typedef struct s_env
{
    void    *mlx;
    void    *win;
    void    *img;

    char    *data;
    int     bpp;
    int     size_line;
    int     endian;
    t_player player;

    char    **map;

    t_tex   tex[TEX_MAX];  // 4 textures N/E/S/O
}   t_env;



// typedef struct s_env
// {
// 	void	*mlx;
// 	void	*win;
// 	void	*img;

// 	char	*data;
// 	int	bpp;
// 	int	size_line;
// 	int	endian;
// 	t_player	player;

// 	char	**map;
// }	t_env;

// typedef struct s_hit {
// 	float	dist;
// 	float	x;
// 	float	y;
// 	int		color;
// } t_hit;

typedef struct s_rayinfo
{
	float	dirx;
	float	diry;
	float	inv_dirx;
	float	inv_diry;
	float	deltaX;
	float	deltaY;
	float	sideX;
	float	sideY;
	int		mapx;
	int		mapy;
	int		stepX;
	int		stepY;
	int		side;
	float	cellx;
	float	celly;
}	t_rayinfo;

//player.c :
void	init_player(t_player *player);
int		keypress(int keycode, t_player *player);
void	move_player(t_player *player);
int	key_release(int keycode, t_player *player);

//main.c :
int		draw_loop(t_env *env);
void	put_pixel(int x, int y, int color, t_env *env);
void	clear_image(t_env *env);
void	draw_square(int x, int y, int size, int color, t_env *env);
char	**get_map(void);
void	draw_map(t_env *env);
void	init_env(t_env *env);
bool	touch(float px, float py, t_env *env);
float	distance(float x, float y);
float	fixed_dist(float x1, float y1, float x2, float y2, t_env *env);

// textures.c
int  load_textures(t_env *env);
void destroy_textures(t_env *env);

// draw_textured.c
void draw_textured_column(int col_x, int y0, int y1,
                          int orig_y0, int lineH,
                          const t_hit *h, t_env *env);


#endif
