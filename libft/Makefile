# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bamsyah <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/04 17:58:02 by bkaztaou          #+#    #+#              #
#    Updated: 2023/11/16 21:51:41 by bamsyah          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

FILES = $(wildcard *.c)

OBJ = $(FILES:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@ar rc $(NAME) $(OBJ) >/dev/null

$(OBJ) : $(FILES)
	@$(CC) $(CFLAGS) -c $(FILES) >/dev/null

clean:
	@rm -rf $(OBJ) >/dev/null

fclean: clean
	@rm -rf $(NAME) >/dev/null

re: fclean all
