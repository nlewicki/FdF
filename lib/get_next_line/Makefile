# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/12 11:46:20 by nlewicki          #+#    #+#              #
#    Updated: 2024/10/30 09:35:26 by nlewicki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


files = get_next_line.c \
		get_next_line_utils.c \

Compiler = cc
CmpFlags = -Wall -Wextra -Werror
CFILES   = $(files)
OFILES   = $(files:.c=.o)
NAME     = get_next_line.a

$(NAME): $(OFILES)
	@ar rsc $(NAME) $(OFILES)

all: $(NAME)

clean:
	@rm -f $(OFILES) $(bonus:.c=.o)

fclean: clean
	@rm -f $(NAME)

re: fclean all

bonus: $(bonus:.c=.o)
	@$(AR) -r $(NAME) $?

.PHONY: all, clean, fclean, re, bonus
