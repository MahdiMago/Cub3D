NAME = libparsing.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = parsing/check_map.c \
      parsing/parsing.c \
      parsing/skiplines_handler.c \
      utils/utils.c \
      utils/utils2.c \
      utils/utils3.c \
      utils/utils4.c \
      utils/utils5.c \
	  utils/check_paths.c

OBJ = $(SRC:.c=.o)

INCLUDES = -I ../libft -I parsing

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Création de la librairie parsing..."
	ar rcs $(NAME) $(OBJ)
	@echo "✅ $(NAME) créée !"

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
