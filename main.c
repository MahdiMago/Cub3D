#include "parsing.h"

// Fonction d'affichage de debug
void	print_debug_info(t_map *map)
{
	int	i;

	printf("\n====================================\n");
	printf("       🔍 DEBUG PARSING INFO       \n");
	printf("====================================\n");

	// 1. Les compteurs de validation
	printf("\n[1] CHECKS TEXTURES :\n");
	printf("NO: %d | SO: %d | WE: %d | EA: %d\n", map->no, map->so, map->we, map->ea);

	// 2. Les lignes de configuration (Avant la map)
	printf("\n[2] CONFIGURATION (before_map) :\n");
	i = 0;
	if (map->before_map)
	{
		while (map->before_map[i])
		{
			printf("  -> Ligne %d : %s\n", i, map->before_map[i]);
			i++;
		}
	}
	else
		printf("  (NULL)\n");

	// 3. La Map Rectangulaire (Celle avec les 'V')
	// J'ajoute des pipes | au début et à la fin pour bien voir les espaces/V
	printf("\n[3] MAP RECTANGULAIRE (rectangular_map) :\n");
	i = 0;
	if (map->rectangular_map)
	{
		while (map->rectangular_map[i])
		{
			printf("  |%s|\n", map->rectangular_map[i]);
			i++;
		}
	}
	else
		printf("  (NULL)\n");

	// 4. Dimensions et Infos diverses
	printf("\n[4] DIMENSIONS & INFOS :\n");
	printf("  -> Hauteur (height) : %d\n", map->height);
	printf("  -> Largeur max (biggest_len) : %d\n", map->biggest_len);
	
	// Note : start_x et start_y seront à 0 si tu ne les as pas sauvegardés
	// dans check_map -> find_position
	printf("  -> Joueur Start X : %d\n", map->start_x);
	printf("  -> Joueur Start Y : %d\n", map->start_y);
	printf("\n====================================\n\n");
}

int	main(int ac, char **av)
{
	t_env	env;

	// 1. Allouer la mémoire
	env.map2 = malloc(sizeof(t_map));
	if (!env.map2)
		return (1);

	// 2. IMPORTANT : Initialiser tout à 0 pour éviter les bugs de compteurs
	// (Assure-toi que ft_bzero est accessible via libft.h)
	ft_bzero(env.map2, sizeof(t_map));

	if (parsing(ac, av, env.map2) == 0)
	{
		// Si le parsing est bon, on affiche tout ce qu'on a trouvé
		print_debug_info(env.map2);
		
		printf("✅ SUCCESS: Map chargée et valide (trop chaud mgl)\n");
		
		// Ici tu lancerais la MLX...
	}
	else
	{
		printf("❌ ERROR: Parsing échoué (tie nul ahhh)\n");
		// Pense à free env.map2 ici aussi si tu veux être propre
		free(env.map2);
		return (1);
	}

	// Nettoyage final (à adapter avec ta fonction free_maps plus tard)
	// free_maps(env.map2);
	// free(env.map2);
	return (0);
}
