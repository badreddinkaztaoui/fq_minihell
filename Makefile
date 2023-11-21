# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bkaztaou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/17 08:31:30 by bkaztaou          #+#    #+#              #
#    Updated: 2023/11/22 00:11:37 by bkaztaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
READLINE = -lreadline
LIBFT = -L./libft -lft

FILES = ./src/minishell.c \
			$(wildcard ./src/parser/*.c) $(wildcard ./src/lexer/*.c) $(wildcard ./utils/*.c)
OBJ = $(FILES:.c=.o)

GREEN = \033[0;32m
ORANGE = \033[0;33m
RED = \033[0;31m
NC = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C ./libft >/dev/null
	@echo "$(GREEN)Compiling libft...$(NC)"
	@$(CC) $(CFLAGS) $(OBJ) $(READLINE) $(LIBFT) -o $(NAME) >/dev/null
	@echo "$(ORANGE)Linking $(NAME)...$(NC)"

$(OBJ): %.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ >/dev/null
	@echo "$(GREEN)Compiling $<$(NC)"

clean:
	@$(MAKE) -C ./libft fclean
	@echo "$(RED)Cleaning libft...$(NC)"
	@rm -rf $(OBJ)
	@echo "$(RED)Cleaning objects...$(NC)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)Cleaning $(NAME)...$(NC)"

re: fclean all

.PHONY: all clean fclean re