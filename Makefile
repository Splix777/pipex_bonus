# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsalazar <fsalazar@student.42madrid.com:>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/25 12:50:19 by fsalazar          #+#    #+#              #
#    Updated: 2023/05/25 12:50:23 by fsalazar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address

RM = rm -f

SRC	=	src/pipex.c		\
		src/childs.c	\
		src/errors.c	\
		src/utils.c		\
		src/frees.c

SRCB =	src_bonus/childs_bonus.c	\
		src_bonus/errors_bonus.c	\
		src_bonus/frees_bonus.c		\
		src_bonus/here_doc.c 		\
		src_bonus/do_pipex.c		\
		src_bonus/main.c			\
		src_bonus/utils_bonus.c

OBJ = $(SRC:.c=.o)

OBJB = $(SRCB:.c=.o)

LIBFT = ./libft/libft.a
PRINTF = ./ft_printf/libftprintf.a

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ./libft
	@make -C ./ft_printf
	@$(CC) $(CFLAGS) -o pipex $(OBJ) $(LIBFT) $(PRINTF)

bonus: $(OBJB)
	@make -C ./libft
	@make -C ./ft_printf
	@$(CC) $(CFLAGS) -o pipex $(OBJB) $(LIBFT) $(PRINTF)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C ./libft
	@make clean -C ./ft_printf
	@$(RM) $(OBJ) $(OBJB)

fclean: clean
	@make fclean -C ./libft
	@make fclean -C ./ft_printf
	@$(RM) $(NAME) $(OBJB)
	@$(RM) pipex

re: fclean all

.PHONY: all clean fclean re bonus
