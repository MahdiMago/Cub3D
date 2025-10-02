NAME = cub3d
CC = cc
SRC = src/main.c src/player.c
OBJ = $(SRC:.c=.o)

LFLAGS = -L./includes/mlx -lmlx -lXext -lX11 -lm -lz
INCLUDES = includes/mlx/libmlx.a

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(INCLUDES) $(LFLAGS)

%.o: %.c
	$(CC) -c $< -o $@

fclean:
	rm -rf $(OBJ)
	rm -rf $(NAME)

re: fclean all
