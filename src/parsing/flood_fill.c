/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 18:36:31 by mamagoma          #+#    #+#             */
/*   Updated: 2025/12/25 18:37:11 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_rectangular(char **rec_map)
{
	int	i;
	int	j;

	i = 0;
	while (rec_map[i])
	{
		j = 0;
		while (rec_map[i][j])
		{
			if (rec_map[i][j] == 'V')
			{
				big_condition(rec_map, i, j);
			}
			j++;
		}
		i++;
	}
}

void	big_condition(char **rec_map, int i, int j)
{
	if ((rec_map[i + 1] && (rec_map[i + 1][j] == '0'
			|| rec_map[i + 1][j] == 'N'
		|| rec_map[i + 1][j] == 'S' || rec_map[i + 1][j] == 'E'
				|| rec_map[i + 1][j] == 'W')) || (i > 0 && (rec_map[i
				- 1][j] == '0' || rec_map[i - 1][j] == 'N' || rec_map[i
				- 1][j] == 'S' || rec_map[i - 1][j] == 'E' || rec_map[i
				- 1][j] == 'W')) || (rec_map[i][j + 1] && (rec_map[i][j
				+ 1] == '0' || rec_map[i][j + 1] == 'N' || rec_map[i][j
				+ 1] == 'S' || rec_map[i][j + 1] == 'E' || rec_map[i][j
				+ 1] == 'W')) || (j > 0 && (rec_map[i][j - 1] == '0'
				|| rec_map[i][j - 1] == 'N' || rec_map[i][j - 1] == 'S'
				|| rec_map[i][j - 1] == 'E' || rec_map[i][j - 1] == 'W')))
	{
		ft_error("error: space found inside the map\n", rec_map);
		exit(1);
	}
}
