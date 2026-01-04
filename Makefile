NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

# --- 1. DÉFINITION DES CHEMINS (PATHS) ---
# Dossier de la MLX
MLX_PATH = includes/mlx

# Dossier où se trouve "libparsing.a"
PARSING_PATH = includes/parsing

# Dossier où se trouve "libft.a" (dans includes/parsing/libft)
LIBFT_PATH = includes/parsing/libft

# --- 2. SOURCES ---
SRC = src/main.c src/player.c src/raycast.c src/textures.c \
      src/draw_textured.c src/draw_utils.c src/raycast_utils.c \
      src/init_main.c src/raycast_2.c src/close.c src/player_utils.c

OBJ = $(SRC:.c=.o)

# --- 3. INCLUDES (-I) ---
# Sert à dire : "Si tu vois #include <header.h>, cherche dans ces dossiers"
# On ajoute le dossier de parsing pour qu'il trouve parsing.h
# On ajoute le dossier de libft pour qu'il trouve libft.h
INCLUDES = -I includes -I $(MLX_PATH) -I $(PARSING_PATH) -I $(LIBFT_PATH)

# --- 4. LIBRARY FLAGS (-L et -l) ---
# C'est ici que la magie du "Linker" opère.
# -L : "Regarde dans ce dossier"
# -l : "Charge ce fichier .a" (ex: -lparsing charge libparsing.a)
# Ordre important : MLX, puis Parsing, puis Libft (car parsing dépend de libft)
LFLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm -lz \
         -L$(PARSING_PATH) -lparsing \
         -L$(LIBFT_PATH) -lft

# --- RÈGLES ---

all: $(NAME)

$(NAME): $(OBJ)
	@echo "🚀 Édition de liens (Linking) en cours..."
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LFLAGS)
	@echo "✅ Cub3D compilé avec succès !"

# Compilation des fichiers .c en .o
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

run: re
	./$(NAME) maps/map.cub

.PHONY: all clean fclean re run
