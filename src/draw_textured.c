#include "../includes/cub3d.h"
#include <math.h>

// Lecture d'un pixel d'une texture (32 bits)
static inline unsigned int texel(const t_tex *t, int x, int y)
{
    char *p = t->addr + y * t->ll + x * (t->bpp >> 3);
    return *(unsigned int *)p; // BGRA (X11) mais on copie 32b → 32b, donc OK
}

// Ecrit un pixel dans ton framebuffer
static inline void put_px_img(t_env *env, int x, int y, unsigned int c)
{
    if ((unsigned)x >= WIDTH || (unsigned)y >= HEIGH) return;
    char *p = env->data + y * env->size_line + x * (env->bpp >> 3);
    *(unsigned int *)p = c;
}

// Choix de la texture selon la face touchée (orientation)
static inline const t_tex *pick_texture(const t_hit *h, const t_env *env)
{
    if (h->side == 0) // mur vertical (on a traversé une ligne X) → Est/Ouest
        return (h->stepX > 0) ? &env->tex[TEX_WEST] : &env->tex[TEX_EAST];
    else              // mur horizontal → Nord/Sud
        return (h->stepY > 0) ? &env->tex[TEX_NORTH] : &env->tex[TEX_SOUTH];
}

void draw_textured_column(int col_x, int y0, int y1,
                          int orig_y0, int lineH,
                          const t_hit *h, t_env *env)
{
    const t_tex *tex = pick_texture(h, env);
    const int texW = tex->w;
    const int texH = tex->h;

    double wallX = (h->side == 0)
                 ? fmod(h->y, (double)BLOCK) / (double)BLOCK
                 : fmod(h->x, (double)BLOCK) / (double)BLOCK;
    int texX = (int)(wallX * (double)texW);
    if ((h->side == 0 && h->stepX > 0) || (h->side == 1 && h->stepY < 0))
        texX = texW - texX - 1;

    double step   = (double)texH / (double)lineH;

    double texPos = ((double)orig_y0 - (double)HEIGH / 2.0 + (double)lineH / 2.0) * step;

    texPos += (double)(y0 - orig_y0) * step;

    for (int y = y0; y <= y1; ++y) {
        int texY = (int)texPos;
        if ((unsigned)texY >= (unsigned)texH) texY = texH - 1;
        texPos += step;

        unsigned int c = texel(tex, texX, texY);
        if (h->side == 1) c = ((c >> 1) & 0x7F7F7F) | (c & 0xFF000000);
        put_px_img(env, col_x, y, c);
    }
}
