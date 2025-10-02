
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
    map[5] = "100000010000001";
    map[6] = "100001000000001";
    map[7] = "100000000000001";
    map[8] = "100000000000001";
    map[9] = "111111111111111";
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

int	draw_loop(t_env *env)
{
	t_player	*player = &env->player;
	move_player(player);
	clear_image(env);
	draw_square(player->x, player->y, 10, 0x00FF00, env);
	draw_map(env);

	float	ray_x = player->x;
	float	ray_y = player->y;
	float	cos_angle = cos(player->angle);
	float	sin_angle = sin(player->angle);

	while(!touch(ray_x, ray_y, env))
	{
		put_pixel(ray_x, ray_y, 0xFF0000, env);
		ray_x += cos_angle;
		ray_y += sin_angle;
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
