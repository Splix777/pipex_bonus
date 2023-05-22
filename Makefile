NAME = pipex.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

RM = rm -f

SRC	=	src/pipex.c		\
		src/childs.c	\
		src/errors.c	\
		src/utils.c		\
		src/frees.c

OBJ = $(SRC:.c=.o)

LIBFT = ./libft/libft.a
PRINTF = ./ft_printf/libftprintf.a

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ./libft
	@make -C ./ft_printf
	@$(CC) $(CFLAGS) -o pipex $(OBJ) $(LIBFT) $(PRINTF)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C ./libft
	@make clean -C ./ft_printf
	@$(RM) $(OBJ)

fclean: clean
	@make fclean -C ./libft
	@make fclean -C ./ft_printf
	@$(RM) $(NAME)
	@$(RM) pipex

re: fclean all

.PHONY: all clean fclean re
