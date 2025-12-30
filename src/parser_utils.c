/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auto <auto@local>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 12:30:00 by auto              #+#    #+#             */
/*   Updated: 2025/12/30 12:30:00 by auto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser_utils.h"
#include "../includes/cub3d.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *trim(char *s)
{
    char *end;

    while (*s && isspace((unsigned char)*s))
        s++;
    if (*s == '\0')
        return (s);
    end = s + strlen(s) - 1;
    while (end > s && isspace((unsigned char)*end))
    {
        *end = '\0';
        end--;
    }
    return (s);
}

int get_color(const char *s)
{
    int r;
    int g;
    int b;

    r = 0;
    g = 0;
    b = 0;
    if (sscanf(s, "%d,%d,%d", &r, &g, &b) != 3)
        return (-1);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return (-1);
    return ((r << 16) | (g << 8) | b);
}

int tex_id(const char *k)
{
    if (strcmp(k, "NO") == 0)
        return (TEX_NORTH);
    if (strcmp(k, "SO") == 0)
        return (TEX_SOUTH);
    if (strcmp(k, "EA") == 0)
        return (TEX_EAST);
    if (strcmp(k, "WE") == 0)
        return (TEX_WEST);
    return (-1);
}

char *clean_map_line(const char *s)
{
    size_t i;
    size_t j;
    size_t len;
    char *out;

    len = strlen(s);
    out = malloc(len + 1);
    if (!out)
        return (NULL);
    i = 0;
    j = 0;
    while (i < len)
    {
        if (!isspace((unsigned char)s[i]))
            out[j++] = s[i];
        i++;
    }
    out[j] = '\0';
    if (j == 0)
    {
        free(out);
        return (NULL);
    }
    return (out);
}

int map_append(char ***map, int *mapc, char *clean)
{
    char **tmp;

    tmp = realloc(*map, (*mapc + 2) * sizeof(*tmp));
    if (!tmp)
    {
        return (0);
    }
    *map = tmp;
    (*map)[(*mapc)++] = clean;
    (*map)[*mapc] = NULL;
    return (1);
}
