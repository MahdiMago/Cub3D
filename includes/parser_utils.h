/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auto <auto@local>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 12:30:00 by auto              #+#    #+#             */
/*   Updated: 2025/12/30 12:30:00 by auto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

typedef struct s_parsing t_parsing;

char	*trim(char *s);
int	get_color(const char *s);
int	tex_id(const char *k);
char	*clean_map_line(const char *s);
int	map_append(char ***map, int *mapc, char *clean);

#endif
