/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:30:12 by mamagoma          #+#    #+#             */
/*   Updated: 2026/01/04 21:34:39 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define ESC 65307
# define D 100
# define A 97
# define W 119
# define S 115
# define LEFT 65361
# define RIGHT 65363
# define RS 0.02
# define MOVESPEED 0.02

typedef struct s_map
{
	char			**map_copy;
	char			**skip_map;
	char			**before_map;
	char			**after_map;
	char			**rectangular_map;
	char			**dummy_map;
	char			**trim_map;
	char			*trim_str;
	int				biggest_len;
	int				i;
	int				j;
	int				current_len;
	int				start_x;
	int				start_y;
	int				height;
	int				length;
	int				no;
	int				so;
	int				ea;
	int				we;
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	unsigned long	floor_color;
	unsigned long	ceiling_color;
}				t_map;

int				parsing(int argc, char **argv, t_map *map);
char			**make_rectangular(char **map_copy, t_map *map);
char			**copy_map(char *argv);
void			check_map(char **map_copy);
int				check_characters(char *map_copy);
void			check_rectangular(char **rec_map);
void			long_condition(char **rec_map, int i, int j);
char			**skip_lines(char **map_copy, char *argv, t_map *map);
void			after_copy(t_map *map, int i, char *argv, char **map_copy);
void			check_fd(int fd);
int				check_file_name(char *argv);
int				count_lines(char *argv);
void			print_map(char **map);
int				is_space(char *str);
int				find_biggest_len(char **map);
char			**map_scan(char **map, char *argv);
void			ft_error(char *str, char **map);
void			free_map(char **map);
int				check_nums(char *str);
void			check_paths(t_map *map);
void			check_instructions(char **before_map);
void			free_maps(t_map *map);
void			check_doubles(char **map_copy);
void			find_position(char **map_copy);
void			error(int x, int y);
int				is_alpha(char *str);
int				check_xpm(char *str);
void			check_rgb(char *str);
void			check_c_f(char **split_str);
void			doubles_check(char **before_map);
void			check2(char **map);
int				condition(int c, t_map *map);
int				cal_h(char **map);
unsigned long	convert_rgb(char *str);

#endif
