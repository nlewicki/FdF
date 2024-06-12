# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/12 10:45:16 by nlewicki          #+#    #+#              #
#    Updated: 2024/06/12 13:14:55 by nlewicki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFILES = FdF.c \

NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -Iminilibx_macos -Lminilibx_macos -lmlx -framework OpenGL -framework AppKit
OBJS = $(CFILES:.c=.o)

# directories and libraries
LIBFT_DIR = lib/libft
LIBFT = $(LIBFT_DIR)/libft.a

PRINTF_DIR = lib/ft_printf
PRINTF = $(PRINTF_DIR)/libftprintf.a

GNL_DIR = lib/get_next_line
GNL = $(GNL_DIR)/get_next_line.a

MINILIBX = minilibx_macos/libmlx.a

$(NAME): libft printf gnl minilibx $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS) -o $(NAME) $(LIBFT) $(PRINTF) $(GNL) $(MINILIBX)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# build printf and libft
printf:
	@make -C $(PRINTF_DIR)

libft:
	@make -C $(LIBFT_DIR)

gnl:
	@make -C $(GNL_DIR)

minilibx:
	@make -C minilibx_macos

all: $(NAME)

clean:
	rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@make -C $(PRINTF_DIR) clean
	@make -C $(GNL_DIR) clean
	@make -C minilibx_macos clean

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT) $(PRINTF) $(GNL) $(MINILIBX)

re: fclean all

.PHONY: all clean fclean re libft printf gnl minilibx
