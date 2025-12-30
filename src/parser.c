/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auto <auto@local>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 12:00:00 by auto              #+#    #+#             */
/*   Updated: 2025/12/30 12:00:00 by auto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/parser_utils.h"
#include <ctype.h>
#include <stdio.h>

int parse_file(const char *path, t_parsing *par)
{
    FILE *f;
    char *line;
    size_t len;
    ssize_t rd;
    char **map;
    int mapc;
    int i;

    if (!par)
        return (0);
    par->map = NULL;
    par->color_ceiling = -1;
    par->color_floor = -1;
    i = 0;
    while (i < TEX_MAX)
    {
        par->tex_path[i] = NULL;
        i++;
    }
    f = fopen(path, "r");
    if (!f)
        return (0);
    line = NULL;
    len = 0;
    map = NULL;
    mapc = 0;
    while ((rd = getline(&line, &len, f)) != -1)
    {
        char *s;

        s = trim(line);
        if (*s == '\0')
            continue;
        {
            char key[4];
            char val[1024];
            char *clean;
            int id;

            key[0] = '\0';
            val[0] = '\0';
            if (s[0] && s[1] && (s[2] == ' ' || s[2] == '\t') &&
                sscanf(s, "%3s %1023s", key, val) >= 2)
            {
                id = tex_id(key);
                if (id >= 0)
                {
                    par->tex_path[id] = strdup(val);
                    continue;
                }
            }
            if (s[0] == 'F' && isspace((unsigned char)s[1]))
            {
                int col;

                col = get_color(s + 1);
                if (col >= 0)
                    par->color_floor = col;
                continue;
            }
            if (s[0] == 'C' && isspace((unsigned char)s[1]))
            {
                int col;

                col = get_color(s + 1);
                if (col >= 0)
                    par->color_ceiling = col;
                continue;
            }
            clean = clean_map_line(s);
            if (!clean)
                continue;
            if (!map_append(&map, &mapc, clean))
            {
                free(line);
                fclose(f);
                return (0);
            }
        }
    }
    free(line);
    fclose(f);
    par->map = map;
    return (1);
}