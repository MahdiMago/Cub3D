#include "../includes/cub3d.h"

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
