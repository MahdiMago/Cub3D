/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:20:31 by mamagoma          #+#    #+#             */
/*   Updated: 2026/01/03 13:17:10 by mamagoma         ###   ########.fr       */
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
# define ESCAPE 65307

# define PI 3.14159265358979323846

# include <ctype.h>
# include <string.h>
# include "mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

typedef struct s_env	t_env;

typedef struct s_tex
{
	void	*img;
	char	*addr;
	int		w;
	int		h;
	int		bpp;
	int		ll;
	int		endian;
}	t_tex;

typedef enum s_texid
{
	TEX_NORTH = 0,
	TEX_SOUTH = 1,
	TEX_EAST = 2,
	TEX_WEST = 3,
	TEX_MAX = 4
}	t_texid;

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;

	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;

	bool	left_rotate;
	bool	right_rotate;

	t_env	*env;
}	t_player;

typedef struct s_hit
{
	float	dist;
	float	x;
	float	y;
	int		color;

	int		side;
	int		stepx;
	int		stepy;
}	t_hit;

typedef struct s_parsing
{
	char	**map;
	int		color_ceiling;
	int		color_floor;
	t_tex	tex[TEX_MAX];
	char	*tex_path[TEX_MAX];
}	t_parsing;

typedef struct s_env
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
	t_player	player;
	t_parsing	parsing;
}	t_env;

int		parse_file(const char *path, t_parsing *parsing);

typedef struct s_rayinfo
{
	float	dirx;
	float	diry;
	float	inv_dirx;
	float	inv_diry;
	float	deltax;
	float	deltay;
	float	sidex;
	float	sidey;
	int		mapx;
	int		mapy;
	int		stepx;
	int		stepy;
	int		side;
	float	cellx;
	float	celly;
}	t_rayinfo;

typedef struct s_drawvars
{
	float	proj_distance;
	int		col_h;
	int		y0;
	int		y1;
	int		orig_y0;
	int		y;
}	t_drawvars;

typedef struct s_distvars
{
	float	x1;
	float	y1;
	float	x2;
	float	y2;
}	t_distvars;

typedef struct s_loop_vars
{
	float	fov;
	float	start;
	float	step;
	int		i;
}	t_loop_vars;

typedef struct s_compute_vars
{
	float	dist;
	float	ix;
	float	iy;
}	t_compute_vars;

typedef struct s_tex_vars
{
	const t_tex	*tex;
	int			tex_w;
	int			tex_h;
	int			tex_x;
	int			tex_y;
	double		wall_x;
	double		step;
	double		tex_pos;
	int			col_x;
}	t_tex_vars;

void	init_player(t_player *player);
int		keypress(int keycode, t_player *player);
int		key_release(int keycode, t_player *player);
void	move_player(t_player *player);

int		draw_loop(t_env *env);
void	put_pixel(int x, int y, int color, t_env *env);
void	clear_image(t_env *env);
void	draw_square(int x, int y, int color, t_env *env);
char	**get_map(void);
void	draw_map(t_env *env);
void	init_env(t_env *env, const char *map_path);
bool	touch(float px, float py, t_env *env);
float	distance(float x, float y);
float	fixed_dist(t_distvars dis_vars, t_env *env);

bool	is_solid_cell(t_env *env, int mx, int my);
void	draw_column(int col_x, t_hit *h, t_env *env, float fov);
void	init_ray_dir(float ray_ang, t_rayinfo *r);
void	init_ray_grid(const t_player *p, t_rayinfo *r);
void	set_inverse_dirs(t_rayinfo *r);

void	init_ray_steps(t_rayinfo *r);
void	perform_dda(t_env *env, t_rayinfo *r);
void	compute_hit(const t_player *p, t_rayinfo *r, t_hit *hit);

int		load_textures(t_env *env);
void	destroy_textures(t_env *env);
void	cast_ray(const t_player *p, float ray_ang, t_env *env, t_hit *hit);

void	draw_textured_column(int col_x, t_drawvars vars,
			const t_hit *h, t_env *env);
int		close_window(t_env *env);
void	init_player_pos(t_env *env);
void	calculate_distance(t_hit *h, t_env *env);
void	calculate_column_params(t_drawvars *vars, t_hit *h, float fov);
void	draw_ceiling(int col_x, t_drawvars *vars, t_env *env);
void	draw_floor(int col_x, t_drawvars *vars, t_env *env);

char	*trim(char *s);
int		get_color(const char *s);
int		tex_id(const char *k);
char	*clean_map_line(const char *s);
int		map_append(char ***map, int *mapc, char *clean);
void	init_parsing(t_parsing *par);
int		parse_texture(char *s, t_parsing *par);
int		parse_color_floor(char *s, t_parsing *par);
int		parse_color_ceiling(char *s, t_parsing *par);
int		process_line(char *s, t_parsing *par, char ***map, int *mapc);
int		read_file_lines(FILE *f, t_parsing *par, char ***map, int *mapc);
int		parse_file(const char *path, t_parsing *par);

#endif
