NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

MLX_PATH = includes/mlx

PARSING_PATH = includes/parsing

LIBFT_PATH = includes/parsing/libft

SRC = src/main.c src/player.c src/raycast.c src/textures.c \
	src/draw_textured.c src/draw_utils.c src/raycast_utils.c \
	src/init_main.c src/raycast_2.c src/close.c src/player_utils.c \
	src/close_utils.c \

OBJ = $(SRC:.c=.o)

INCLUDES = -I includes -I $(MLX_PATH) -I $(PARSING_PATH) -I $(LIBFT_PATH)

LFLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm -lz \
         -L$(PARSING_PATH) -lparsing \
         -L$(LIBFT_PATH) -lft

all: $(NAME)

$(NAME): $(OBJ)
	@echo "🚀 Édition de liens (Linking) en cours..."
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LFLAGS)
	@echo "✅ Cub3D compilé avec succès !"

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
