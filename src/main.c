/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:45:07 by mamagoma          #+#    #+#             */
/*   Updated: 2026/01/03 13:17:02 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_env	env;

	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <map.cub>\n", argv[0]);
		return (1);
	}
	init_env(&env, argv[1]);
	mlx_hook(env.win, 2, 1L << 0, keypress, &env.player);
	mlx_hook(env.win, 3, 1L << 1, key_release, &env.player);
	mlx_hook(env.win, 17, 0, close_window, &env);
	mlx_loop_hook(env.mlx, draw_loop, &env);
	mlx_loop(env.mlx);
	return (0);
}
