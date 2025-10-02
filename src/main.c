
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
		put_pixel(x + i, y, color, env);
	for(int i = 0; i < size; i++)
		put_pixel(x + size, y + i, color, env);
	for(int i = 0; i < size; i++)
		put_pixel(x, y + i, color, env);
	for(int i = 0; i < size; i++)
		put_pixel(x + i, y + size, color, env);
}
char **get_map(void)
{
    char **map = malloc(sizeof(char *) * 11);
    map[0] = "111111111111111";
    map[1] = "100000000000001";
    map[2] = "100000000000001";
    map[3] = "100000100000001";
    map[4] = "100000000000001";
    map[5] = "1000000100000011111111111";
    map[6] = "1000010000000011111100001";
    map[7] = "1000000000000011111000001";
    map[8] = "1000000000000000000011111";
    map[9] = "111111111111111111111";
    map[10] = NULL;
    return (map);
}

void	draw_map(t_env *env)
{
	char	**map = env->map;
	int	color = 0x0000FF;
	for(int y = 0; map[y]; y++)
		for(int x = 0; map[y][x]; x++)
			if(map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, color, env);
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

	if (env->map[y][x] == '1')
		return (true);
	return (false);
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
	}
	
	if (!DEBUG)
	{
		float	dist = fixed_dist(player->x, player->y, ray_x, ray_y, env);
		float	heigh = (BLOCK / dist) * (WIDTH / 2);
		int		start_y = (HEIGH - heigh) / 2;
		int		end = start_y + heigh;

		while (start_y < end)
		{
			put_pixel(i, start_y, 250, env);
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

int	main(void)
{
	t_env	env;

	init_env(&env);

	mlx_hook(env.win, 2, 1L<<0, keypress, &env.player);
	mlx_hook(env.win, 3, 1L<<1, key_release, &env.player);

	mlx_loop_hook(env.mlx, draw_loop, &env);
	mlx_loop(env.mlx);
	return (0);
}
