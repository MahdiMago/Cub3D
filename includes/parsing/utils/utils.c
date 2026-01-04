/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:28:41 by mamagoma          #+#    #+#             */
/*   Updated: 2026/01/04 21:28:42 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"

void	check_fd(int fd)
{
	if (fd == -1)
	{
		printf("map is not accessible\n");
		close(fd);
		exit(1);
	}
}

int	check_file_name(char *argv)
{
	if (ft_strncmp(argv + ft_strlen(argv) - 4, ".cub", 4))
	{
		printf("error: the extension must be .cub\n");
		exit(1);
	}
	return (0);
}

int	count_lines(char *argv)
{
	char	*lines;
	int		fd;
	int		i;

	i = 0;
	fd = open(argv, O_RDONLY);
	lines = get_next_line(fd);
	while (lines)
	{
		i++;
		free(lines);
		lines = get_next_line(fd);
	}
	close(fd);
	return (i);
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

int	is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 10 && str[i] <= 13)
			return (1);
		i++;
	}
	return (0);
}
