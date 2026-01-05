/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:38:49 by mamagoma          #+#    #+#             */
/*   Updated: 2026/01/05 14:42:43 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_string_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

void	free_extention(t_map *map)
{
	if (map->after_map)
	{
		free(map->after_map);
		map->after_map = NULL;
	}
	if (map->dummy_map)
	{
		free(map->dummy_map);
		map->dummy_map = NULL;
	}
	if (map->rectangular_map)
	{
		free_string_array(map->rectangular_map);
	}
}
