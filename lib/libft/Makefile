# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/12 11:07:18 by nlewicki          #+#    #+#              #
#    Updated: 2024/07/02 14:26:13 by nlewicki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

files = ft_bzero.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_isalpha.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strstrim.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_split.c \
		ft_atoi_base.c \

bonus = ft_lstnew_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstmap_bonus.c \


Compiler = cc
CmpFlags = -Wall -Wextra -Werror
CFILES   = $(files)
OFILES   = $(files:.c=.o)
NAME     = libft.a

$(NAME): $(OFILES)
	ar rsc $(NAME) $(OFILES)

all: $(NAME)

clean:
	rm -f $(OFILES) $(bonus:.c=.o)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: $(bonus:.c=.o)
	$(AR) -r $(NAME) $?

.PHONY: all, clean, fclean, re, bonus

