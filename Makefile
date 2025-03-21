NAME = pipex

CC = cc

CFLAGS = -Wall -Werror -Wextra

SRC =	libft_utils_1.c \
		libft_utils_2.c \
		pipex.c \
		pipex_utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re