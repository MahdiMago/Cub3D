#include "../includes/cub3d.h"

void	put_pixel(int x, int y, int color, t_env *env)
{
	if (x >= WIDTH || y >= HEIGH || x < 0 || y < 0)
		return ;
	
	int	index = y * env->size_line + x * env->bpp / 8;
	env->data[index] = color & 0xFF;
	env->data[index + 1] = (color >> 8) & 0xFF;
	env->data[index + 2] = (color >> 16) & 0xFF;
}

void	clear_image(t_env *env)
{
	for(int y = 0; y < HEIGH; y++)
		for(int x = 0; x < WIDTH; x++)
			put_pixel(x, y, 0, env);
}

void	draw_square(int x, int y, int size, int color, t_env *env)
{
	for(int i = 0; i < size; i++)
		put_pixel(x + i, y, COLOR_NORTH, env);
	for(int i = 0; i < size; i++)
		put_pixel(x + size, y + i, COLOR_SOUTH, env);
	for(int i = 0; i < size; i++)
		put_pixel(x, y + i, COLOR_EAST, env);
	for(int i = 0; i < size; i++)
		put_pixel(x + i, y + size, COLOR_WEST, env);
}
char **get_map(void)
{
	int i = 0;
    char **map = malloc(sizeof(char *) * 11);
    map[i++] = "111111111111111";
    map[i++] = "100000000000001";
    map[i++] = "100000000000001";
    map[i++] = "100000200000001";
    map[i++] = "100000000000001";
    map[i++] = "1000000300000011111111111";
    map[i++] = "1000040000000011111100001";
    map[i++] = "1000000000000011111000001";
    map[i++] = "1000000000000000000011111";
    map[i++] = "111111111111111111111";
    map[i++] = NULL;
    return (map);
}

void	draw_map(t_env *env)
{
	char	**map = env->map;
	for(int y = 0; map[y]; y++)
		for(int x = 0; map[y][x]; x++)
		{
			if(map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, COLOR_NORTH, env);
			else if(map[y][x] == '2')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, COLOR_SOUTH, env);
			else if(map[y][x] == '3')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, COLOR_EAST, env);
			else if(map[y][x] == '4')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, COLOR_WEST, env);
		}
}

<<<<<<< HEAD
=======
typedef struct s_hit {
    float dist;   // distance perpendiculaire en unités "monde" (pixels si BLOCK est en px)
    float x;      // impact x en monde
    float y;      // impact y en monde
    int   color;  // couleur à utiliser (N/E/S/W)
} t_hit;

// Hors-borne = solide. Lignes non rectangulaires supportées (ragged).
static inline bool is_solid_cell(t_env *env, int mx, int my)
{
    if (my < 0 || !env->map[my])          return true; // hors hauteur
    if (mx < 0 || mx >= (int)strlen(env->map[my])) return true; // hors largeur
    char c = env->map[my][mx];
    return (c != '0');
}
static inline void draw_column(int col_x, const t_hit *h, t_env *env, float fov)
{
    // Projection géométrique propre :
    // proj = (WIDTH/2) / tan(FOV/2)
    float proj = (WIDTH * 0.5f) / tanf(fov * 0.5f);

    // Hauteur du mur en pixels
    int col_h = (int)fmaxf(1.0f, (BLOCK * proj) / fmaxf(h->dist, 1e-4f));
    int y0 = (HEIGH - col_h) / 2;
    int y1 = y0 + col_h;

    // On dessine la bande verticale
    for (int y = y0; y < y1; ++y)
        put_pixel(col_x, y, h->color, env);
}
// Retourne un impact DDA avec distance perpendiculaire (corrige le fish-eye nativement)
static inline void cast_ray(const t_player *p, float ray_ang, t_env *env, t_hit *hit)
{
    // Direction du rayon
    float dirx = cosf(ray_ang);
    float diry = sinf(ray_ang);

    // Position de départ en "cellules"
    float cellx = p->x / BLOCK;
    float celly = p->y / BLOCK;

    int mapx = (int)floorf(cellx);
    int mapy = (int)floorf(celly);

    // Longueurs de parcours d'une cellule à l'autre
    // (deltaDist = distance pour passer une frontière verticale/horizontale en coordonnées cellule)
    float inv_dirx = (fabsf(dirx) < 1e-8f) ? (dirx >= 0 ? 1e8f : -1e8f) : 1.0f / dirx;
    float inv_diry = (fabsf(diry) < 1e-8f) ? (diry >= 0 ? 1e8f : -1e8f) : 1.0f / diry;

    float deltaDistX = fabsf(inv_dirx);
    float deltaDistY = fabsf(inv_diry);

    int stepX = (dirx < 0.0f) ? -1 : 1;
    int stepY = (diry < 0.0f) ? -1 : 1;

    float sideDistX, sideDistY;

    // distance initiale jusqu’à la première frontière verticale/horizontale
    if (stepX > 0)
        sideDistX = (floorf(cellx) + 1.0f - cellx) * deltaDistX;
    else
        sideDistX = (cellx - floorf(cellx)) * deltaDistX;

    if (stepY > 0)
        sideDistY = (floorf(celly) + 1.0f - celly) * deltaDistY;
    else
        sideDistY = (celly - floorf(celly)) * deltaDistY;

    int side = -1; // 0 = frontière verticale (mur E/W), 1 = frontière horizontale (mur N/S)

    // DDA : avancer jusqu'à heurter une case solide
    while (1) {
        if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapx += stepX;
            side = 0;
        } else {
            sideDistY += deltaDistY;
            mapy += stepY;
            side = 1;
        }
        if (is_solid_cell(env, mapx, mapy))
            break;
    }

    // Distance perpendiculaire (en unités "cellules"), puis conversion en "monde"
    float perpCellDist;
    if (side == 0) {
        // On a traversé une frontière verticale
        perpCellDist = (mapx - cellx + (1 - stepX) * 0.5f) * (inv_dirx > 0 ? 1.0f : -1.0f) * (1.0f / ( (dirx == 0.0f) ? 1e-8f : dirx));
        perpCellDist = fabsf( (mapx - cellx + (1 - stepX) * 0.5f) * inv_dirx );
    } else {
        // On a traversé une frontière horizontale
        perpCellDist = fabsf( (mapy - celly + (1 - stepY) * 0.5f) * inv_diry );
    }

    // En monde (pixels si BLOCK est en px)
    float dist_world = perpCellDist * BLOCK;

    // Point d'impact en monde
    float ix = p->x + dirx * dist_world;
    float iy = p->y + diry * dist_world;

    // Couleur en fonction de la face heurtée (déterministe)
    int color;
    if (side == 0)           // mur "vertical"
        color = (stepX > 0) ? COLOR_WEST : COLOR_EAST;   // +x => entre par face OUEST
    else                     // mur "horizontal"
        color = (stepY > 0) ? COLOR_NORTH : COLOR_SOUTH; // +y (vers le bas) => face NORD

    hit->dist  = dist_world; // déjà perpendiculaire → pas besoin de cos(angle diff).
    hit->x     = ix;
    hit->y     = iy;
    hit->color = color;
}

>>>>>>> 563f04d (save)
void	init_env(t_env *env)
{
	init_player(&env->player);
	env->player.env = env;
	env->map = get_map();
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIDTH, HEIGH, "World");
	env->img = mlx_new_image(env->mlx, WIDTH, HEIGH);
	env->data = mlx_get_data_addr(env->img, &env->bpp, &env->size_line, &env->endian);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}

bool	touch(float px, float py, t_env *env)
{
	int x = px / BLOCK;
	int y = py / BLOCK;

	if (env->map[y][x] != '0')
		return (true);
	return (false);
}

int	line_color(float px, float py, t_env *env)
{
	int cell_x = (int)(px / BLOCK);
	int cell_y = (int)(py / BLOCK);

	float local_x = fmod(px, BLOCK);
	float local_y = fmod(py, BLOCK);

	float dist_left   = local_x;
	float dist_right  = BLOCK - local_x;
	float dist_top    = local_y;
	float dist_bottom = BLOCK - local_y;

	// On cherche la plus petite distance → c’est le bord touché
	if (dist_left < dist_right && dist_left < dist_top && dist_left < dist_bottom)
		return COLOR_WEST;   // gauche
	else if (dist_right < dist_left && dist_right < dist_top && dist_right < dist_bottom)
		return COLOR_EAST;   // droite
	else if (dist_top < dist_left && dist_top < dist_right && dist_top < dist_bottom)
		return COLOR_NORTH;  // haut
	else
		return COLOR_SOUTH;  // bas
}


float	distance(float x, float y)
{
	return (sqrt((x * x) + (y * y)));
}

float	fixed_dist(float x1, float y1, float x2, float y2, t_env *env)
{
	float	delta_x = x2 - x1;
	float	delta_y = y2 - y1;
	float	angle = atan2(delta_y, delta_x) - env->player.angle;
	float	fixed_dis = distance(delta_x, delta_y) * cos(angle);
	return (fixed_dis);
}

void	draw_line(t_player *player, t_env *env, float start_x, int i)
{
	float	cos_angle = cos(start_x);
	float	sin_angle = sin(start_x);
	float	ray_x = player->x;
	float	ray_y = player->y;

	while (!touch(ray_x, ray_y, env))
	{
		if (DEBUG)
			put_pixel(ray_x, ray_y, 0xFF0000, env);
		ray_x += cos_angle;
		ray_y += sin_angle;
		// if (touch(ray_x, ray_y, env))
		// 	color = 
	}
	
	if (!DEBUG)
	{
		float	dist = fixed_dist(player->x, player->y, ray_x, ray_y, env);
		float	heigh = (BLOCK / dist) * (WIDTH / 2);
		int		start_y = (HEIGH - heigh) / 2;
		int		end = start_y + heigh;
		int		color = line_color(ray_x, ray_y, env);

		while (start_y < end)
		{
			put_pixel(i, start_y, color, env);
			start_y++;
		}
	}
}

<<<<<<< HEAD
int	draw_loop(t_env *env)
{
	t_player	*player = &env->player;
	move_player(player);
	clear_image(env);
	if (DEBUG)
	{
		draw_square(player->x, player->y, 10, 0x00FF00, env);
		draw_map(env);
	}

	float fraction = PI / 3 / WIDTH;
	float start_x = player->angle - PI / 6;
	for (int i = 0; i < WIDTH; i++)
	{
		draw_line(player, env, start_x, i);
		start_x += fraction;
	}

	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);

	return (0);
=======
int draw_loop(t_env *env)
{
    t_player *player = &env->player;
    move_player(player);
    clear_image(env);

    if (DEBUG) {
        draw_square(player->x, player->y, 10, 0x00FF00, env);
        draw_map(env);
    }

    // Raycasting
    const float fov = (float)PI / 3.0f; // 60°
    float start = player->angle - fov * 0.5f;
    float step  = fov / (float)WIDTH;

    for (int i = 0; i < WIDTH; ++i) {
        t_hit h;
        float ray_ang = start + i * step;
        cast_ray(player, ray_ang, env, &h);
        draw_column(i, &h, env, fov);
    }

    mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
    return 0;
>>>>>>> 563f04d (save)
}
