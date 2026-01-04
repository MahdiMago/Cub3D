/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:30:26 by mamagoma          #+#    #+#             */
/*   Updated: 2026/01/04 21:31:04 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
				long_condition(rec_map, i, j);
			}
			j++;
		}
		i++;
	}
}

void	long_condition(char **rec_map, int i, int j)
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
