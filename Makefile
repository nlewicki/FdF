# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/12 10:45:16 by nlewicki          #+#    #+#              #
#    Updated: 2024/10/30 09:32:46 by nlewicki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFILES = src/FdF.c \
		 src/read_map.c \
		 src/read_map_utils.c \
		 src/read_map_utils2.c \
		 src/draw.c \
		 src/draw_color.c \
		 src/utils.c \
		 src/utils2.c \
		 src/free_data.c \

NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -Iminilibx_macos -Lminilibx_macos -lmlx -framework OpenGL -framework AppKit
OBJS = $(CFILES:.c=.o)

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
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@make -C $(PRINTF_DIR) clean
	@make -C $(GNL_DIR) clean
	@make -C minilibx_macos clean
	@echo "\033[90mclean\033[0m"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT) $(PRINTF) $(GNL) $(MINILIBX)
	@echo "\033[90mand\033[0m"
	@echo "\033[90mfclean\033[0m"


re: fclean all

.PHONY: all clean fclean re libft printf gnl minilibx
