/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:35:13 by mamagoma          #+#    #+#             */
/*   Updated: 2026/01/05 20:26:48 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_env	env;

	ft_bzero(&env, sizeof(t_env));
	env.map2 = malloc(sizeof(t_map));
	if (!env.map2)
		return (1);
	ft_bzero(env.map2, sizeof(t_map));
	if (parsing(ac, av, env.map2) != 0)
	{
		if (env.map2)
			free(env.map2);
		return (1);
	}
	init_env(&env);
	mlx_hook(env.win, 2, 1L << 0, keypress, &env.player);
	mlx_hook(env.win, 3, 1L << 1, key_release, &env.player);
	mlx_hook(env.win, 17, 0, close_window, &env);
	mlx_loop_hook(env.mlx, draw_loop, &env);
	mlx_loop(env.mlx);
	return (0);
}
