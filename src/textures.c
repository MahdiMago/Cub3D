#include "../includes/cub3d.h"

static int load_one_tex(t_env *env, const char *path, t_tex *t)
{
    t->img = mlx_xpm_file_to_image(env->mlx, (char *)path, &t->w, &t->h);
    if (!t->img) return 0;
    t->addr = mlx_get_data_addr(t->img, &t->bpp, &t->ll, &t->endian);
    return (t->addr != NULL);
}

int load_textures(t_env *env)
{
    // Adapte les chemins selon ton arborescence
    if (!load_one_tex(env, "./textures/north.xpm", &env->tex[TEX_NORTH])) return 0;
    if (!load_one_tex(env, "./textures/south.xpm", &env->tex[TEX_SOUTH])) return 0;
    if (!load_one_tex(env, "./textures/east.xpm",  &env->tex[TEX_EAST]))  return 0;
    if (!load_one_tex(env, "./textures/west.xpm",  &env->tex[TEX_WEST]))  return 0;
    return 1;
}

void destroy_textures(t_env *env)
{
    for (int i = 0; i < TEX_MAX; ++i)
        if (env->tex[i].img)
            mlx_destroy_image(env->mlx, env->tex[i].img);
}
