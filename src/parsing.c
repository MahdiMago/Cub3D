/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 03:50:35 by mamagoma          #+#    #+#             */
/*   Updated: 2025/09/22 04:03:38 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_map_valid(char **map)
{
	int x = 0;
	int y = -1;
	int flag = 0;

	while (map[++y])
	{
		while (map[y][x])
		{
			if ((y == 0 || !map[y + 1]) && (map[y][x] != '1'))
				return (0);
			else if ((map[y][x - 1] == ' ') && flag == 0)
				flag = 1;
			else if ((map[y][x + 1] == '\n' || map[y][x + 1] == '\0') && flag == 1)
				flag = 0;
			x++;
		}
	}
}
