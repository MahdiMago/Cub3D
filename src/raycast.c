#include "../includes/cub3d.h"

void	put_pixel(int x, int y, int color, t_env *env)
{
	if (x >= WIDTH || y >= HEIGH || x < 0 || y < 0)
		return ;
	
	int	index = y * env->size_line + x * env->bpp / 8;
	env->data[index] = color & 0xFF;
	env->data[index + 1] = (color >> 8) & 0xFF;
	env->data[index + 2] = (color >> 16) & 0xFF;
}

void	clear_image(t_env *env)
{
	for(int y = 0; y < HEIGH; y++)
		for(int x = 0; x < WIDTH; x++)
			put_pixel(x, y, 0, env);
}

void	draw_square(int x, int y, int size, int color, t_env *env)
{
	for(int i = 0; i < size; i++)
		put_pixel(x + i, y, COLOR_NORTH, env);
	for(int i = 0; i < size; i++)
		put_pixel(x + size, y + i, COLOR_SOUTH, env);
	for(int i = 0; i < size; i++)
		put_pixel(x, y + i, COLOR_EAST, env);
	for(int i = 0; i < size; i++)
		put_pixel(x + i, y + size, COLOR_WEST, env);
}
char **get_map(void)
{
	int i = 0;
    char **map = malloc(sizeof(char *) * 11);
    map[i++] = "111111111111111";
    map[i++] = "100000000000001";
    map[i++] = "100000000000001";
    map[i++] = "100000200000001";
    map[i++] = "100000000000001";
    map[i++] = "1000000300000011111111111";
    map[i++] = "1000040000000011111100001";
    map[i++] = "1000000000000011111000001";
    map[i++] = "1000000000000000000011111";
    map[i++] = "111111111111111111111";
    map[i++] = NULL;
    return (map);
}

void	draw_map(t_env *env)
{
	char	**map = env->map;
	for(int y = 0; map[y]; y++)
		for(int x = 0; map[y][x]; x++)
		{
			if(map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, COLOR_NORTH, env);
			else if(map[y][x] == '2')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, COLOR_SOUTH, env);
			else if(map[y][x] == '3')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, COLOR_EAST, env);
			else if(map[y][x] == '4')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, COLOR_WEST, env);
		}
}

void	init_env(t_env *env)
{
	init_player(&env->player);
	env->player.env = env;
	env->map = get_map();
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIDTH, HEIGH, "World");
	env->img = mlx_new_image(env->mlx, WIDTH, HEIGH);
	env->data = mlx_get_data_addr(env->img, &env->bpp, &env->size_line, &env->endian);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}

bool	touch(float px, float py, t_env *env)
{
	int x = px / BLOCK;
	int y = py / BLOCK;

	if (env->map[y][x] != '0')
		return (true);
	return (false);
}

int	line_color(float px, float py, t_env *env)
{
	int cell_x = (int)(px / BLOCK);
	int cell_y = (int)(py / BLOCK);

	float local_x = fmod(px, BLOCK);
	float local_y = fmod(py, BLOCK);

	float dist_left   = local_x;
	float dist_right  = BLOCK - local_x;
	float dist_top    = local_y;
	float dist_bottom = BLOCK - local_y;

	// On cherche la plus petite distance → c’est le bord touché
	if (dist_left < dist_right && dist_left < dist_top && dist_left < dist_bottom)
		return COLOR_WEST;   // gauche
	else if (dist_right < dist_left && dist_right < dist_top && dist_right < dist_bottom)
		return COLOR_EAST;   // droite
	else if (dist_top < dist_left && dist_top < dist_right && dist_top < dist_bottom)
		return COLOR_NORTH;  // haut
	else
		return COLOR_SOUTH;  // bas
}


float	distance(float x, float y)
{
	return (sqrt((x * x) + (y * y)));
}

float	fixed_dist(float x1, float y1, float x2, float y2, t_env *env)
{
	float	delta_x = x2 - x1;
	float	delta_y = y2 - y1;
	float	angle = atan2(delta_y, delta_x) - env->player.angle;
	float	fixed_dis = distance(delta_x, delta_y) * cos(angle);
	return (fixed_dis);
}

void	draw_line(t_player *player, t_env *env, float start_x, int i)
{
	float	cos_angle = cos(start_x);
	float	sin_angle = sin(start_x);
	float	ray_x = player->x;
	float	ray_y = player->y;

	while (!touch(ray_x, ray_y, env))
	{
		if (DEBUG)
			put_pixel(ray_x, ray_y, 0xFF0000, env);
		ray_x += cos_angle;
		ray_y += sin_angle;
		// if (touch(ray_x, ray_y, env))
		// 	color = 
	}
	
	if (!DEBUG)
	{
		float	dist = fixed_dist(player->x, player->y, ray_x, ray_y, env);
		float	heigh = (BLOCK / dist) * (WIDTH / 2);
		int		start_y = (HEIGH - heigh) / 2;
		int		end = start_y + heigh;
		int		color = line_color(ray_x, ray_y, env);

		while (start_y < end)
		{
			put_pixel(i, start_y, color, env);
			start_y++;
		}
	}
}

int	draw_loop(t_env *env)
{
	t_player	*player = &env->player;
	move_player(player);
	clear_image(env);
	if (DEBUG)
	{
		draw_square(player->x, player->y, 10, 0x00FF00, env);
		draw_map(env);
	}

	float fraction = PI / 3 / WIDTH;
	float start_x = player->angle - PI / 6;
	for (int i = 0; i < WIDTH; i++)
	{
		draw_line(player, env, start_x, i);
		start_x += fraction;
	}

	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);

	return (0);
}
