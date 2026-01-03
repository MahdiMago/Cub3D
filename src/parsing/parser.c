/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 10:53:11 by mamagoma          #+#    #+#             */
/*   Updated: 2026/01/03 11:16:50 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_parsing(t_parsing *par)
{
	int	i;

	par->map = NULL;
	par->color_ceiling = -1;
	par->color_floor = -1;
	i = 0;
	while (i < TEX_MAX)
	{
		par->tex_path[i] = NULL;
		i++;
	}
}

int	parse_texture(char *s, t_parsing *par)
{
	char	key[4];
	char	val[1024];
	int		id;

	key[0] = '\0';
	val[0] = '\0';
	if (!s[0] || !s[1] || (s[2] != ' ' && s[2] != '\t'))
		return (0);
	if (sscanf(s, "%3s %1023s", key, val) < 2)
		return (0);
	id = tex_id(key);
	if (id >= 0)
	{
		par->tex_path[id] = strdup(val);
		return (1);
	}
	return (0);
}

int	parse_color_floor(char *s, t_parsing *par)
{
	int	col;

	if (s[0] == 'F' && isspace((unsigned char)s[1]))
	{
		col = get_color(s + 1);
		if (col >= 0)
		{
			par->color_floor = col;
			return (1);
		}
	}
	return (0);
}

int	parse_color_ceiling(char *s, t_parsing *par)
{
	int	col;

	if (s[0] == 'C' && isspace((unsigned char)s[1]))
	{
		col = get_color(s + 1);
		if (col >= 0)
		{
			par->color_ceiling = col;
			return (1);
		}
	}
	return (0);
}
