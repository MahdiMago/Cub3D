/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 11:04:15 by mamagoma          #+#    #+#             */
/*   Updated: 2026/01/03 11:58:40 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	process_line(char *s, t_parsing *par, char ***map, int *mapc)
{
	char	*clean;

	if (parse_texture(s, par))
		return (1);
	if (parse_color_floor(s, par))
		return (1);
	if (parse_color_ceiling(s, par))
		return (1);
	clean = clean_map_line(s);
	if (!clean)
		return (1);
	if (!map_append(map, mapc, clean))
		return (0);
	return (1);
}

int	read_file_lines(FILE *f, t_parsing *par, char ***map, int *mapc)
{
	char	*line;
	size_t	len;
	ssize_t	rd;
	char	*s;

	line = NULL;
	len = 0;
	rd = getline(&line, &len, f);
	while (rd != -1)
	{
		s = trim(line);
		if (*s != '\0')
		{
			if (!process_line(s, par, map, mapc))
			{
				free(line);
				return (0);
			}
		}
		rd = getline(&line, &len, f);
	}
	free(line);
	return (1);
}

int	parse_file(const char *path, t_parsing *par)
{
	FILE	*f;
	char	**map;
	int		mapc;

	if (!par)
		return (0);
	init_parsing(par);
	f = fopen(path, "r");
	if (!f)
		return (0);
	map = NULL;
	mapc = 0;
	if (!read_file_lines(f, par, &map, &mapc))
	{
		fclose(f);
		return (0);
	}
	fclose(f);
	par->map = map;
	return (1);
}
