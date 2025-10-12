#include "../includes/cub3d.h"

int	main(void)
{
	t_env	env;

	init_env(&env);

	mlx_hook(env.win, 2, 1L<<0, keypress, &env.player);
	mlx_hook(env.win, 3, 1L<<1, key_release, &env.player);

	mlx_loop_hook(env.mlx, draw_loop, &env);
	mlx_loop(env.mlx);
	return (0);
}


// #define AAAAAAAAAA 800
// #define RRRRRRR 600

// typedef struct s_amg {
//     void *img;
//     char *addr;
//     int bpp;
//     int ll;
//     int endian;
//     int w;
//     int h;
// } t_amg;

// typedef struct s_anv {
//     void *mlx;
//     void *win;
//     t_amg tex;
// } t_anv;

// unsigned int get_pixel_color(t_amg *img, int x, int y)
// {
//     char *dst = img->addr + (y * img->ll + x * (img->bpp / 8));
//     return *(unsigned int *)dst;
// }

// void put_pixel_to_window(t_anv *env, int x, int y, unsigned int color)
// {
//     mlx_pixel_put(env->mlx, env->win, x, y, color);
// }

// void draw_texture_column(t_anv *env, int screen_x, int tex_x, int screen_RRRRRRR)
// {
//     for (int y = 0; y < screen_RRRRRRR; y++)
//     {
//         // On calcule à quelle position de la texture on doit lire
//         int tex_y = (y * env->tex.h) / screen_RRRRRRR;

//         // On lit la couleur du pixel (colonne fixe tex_x)
//         unsigned int color = get_pixel_color(&env->tex, tex_x, tex_y);

//         // On dessine ce pixel sur la colonne de l’écran
//         put_pixel_to_window(env, screen_x, y + (RRRRRRR - screen_RRRRRRR) / 2, color);
//     }
// }

// int main(void)
// {
//     t_anv env;

//     env.mlx = mlx_init();
//     env.win = mlx_new_window(env.mlx, AAAAAAAAAA, RRRRRRR, "Column Example");

//     // Charger l'image texture
//     env.tex.img = mlx_xpm_file_to_image(env.mlx, "wall.xpm", &env.tex.w, &env.tex.h);
//     env.tex.addr = mlx_get_data_addr(env.tex.img, &env.tex.bpp, &env.tex.ll, &env.tex.endian);
// 	for (int tex_x = 0; tex_x < 64; tex_x++) // chaque colonne de texture
// 	{
// 		int screen_x = tex_x * 1; // espacement à l’écran (par exemple *5 pour mieux voir)
// 		draw_texture_column(&env, screen_x, tex_x, 64);
// 	}



//     mlx_loop(env.mlx);
//     return 0;
// }
