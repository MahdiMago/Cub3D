/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:35:38 by mamagoma          #+#    #+#             */
/*   Updated: 2024/11/26 21:30:53 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*after_line(char *line)
{
	char	*reserve;
	ssize_t	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (0);
	reserve = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*reserve == 0)
	{
		free (reserve);
		return (NULL);
	}
	line[i + 1] = '\0';
	return (reserve);
}

static char	*fill_fonction(int fd, char *buffer, char *reserve)
{
	int		nb_digits;
	char	*tempo;

	nb_digits = 1;
	while (nb_digits > 0)
	{
		
		nb_digits = read(fd, buffer, BUFFER_SIZE);
		if (nb_digits == -1)
		{
			free (reserve);
			return (0);
		}
		else if (nb_digits == 0)
			break ;
		buffer[nb_digits] = '\0';
		if (!reserve)
			reserve = ft_strdup("");
		tempo = reserve;
		reserve = ft_strjoin(tempo, buffer);
		free (tempo);
		tempo = NULL;
		if (ft_strchr(reserve, '\n'))
			break ;
	}
	return (reserve);
}

char	*get_next_line(int fd)
{
	static char	*reserve;
	char		*line;
	char		*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(reserve);
		free(buffer);
		reserve = NULL;
		buffer = NULL;
		return (0);
	}
	line = fill_fonction(fd, buffer, reserve);
	free (buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	reserve = after_line(line);
	return (line);
}

//int	main(int argc, char **argv)
//{
//	int fd;
//	char *line;

//	if (argc != 2)
//	{
//		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
//		return (1);
//	}
//	fd = open(argv[1], O_RDONLY);
//	if (fd == -1)
//	{
//		perror("Error opening file");
//		return (1);
//	}
//	line = get_next_line(fd);
//	if (line)
//	{
//		printf("%s", line);
//		free(line);
//	}
//	else
//		printf("No line to read\n");

//	close(fd);
//	return (0);
//}
