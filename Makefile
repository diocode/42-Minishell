# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/24 15:23:58 by digoncal          #+#    #+#              #
#    Updated: 2023/06/14 18:05:18 by digoncal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all deps clean fclean re

GREEN		= \033[38;5;47m
YELLOW		= \033[38;5;226m
RED			= \033[38;5;196m
CYAN 		= \033[1;36m
RESET 		= \033[0m

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

NAME = minishell

SRC = src/main.c src/init.c src/free.c src/signals.c src/utils.c \
	src/env.c src/lexer.c \
	src/builtins/ms_exit.c

OBJ = $(SRC:.c=.o)

LIBFT = libs/libft/libft.a

all: deps $(NAME)
	@echo "[$(GREEN)DONE$(RESET)]:\t\t $(GREEN)minishell$(RESET)"

deps:
	@echo "[$(CYAN)compiling$(RESET)]:\t $(CYAN)Source files & Libraries$(RESET)"
	@$(MAKE) -C ./libs/libft

$(NAME): $(OBJ) $(DEPS)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

clean:
	@echo "$(YELLOW)Removing objects files$(RESET)"
	@$(MAKE) $@ -C ./libs/libft
	@rm -rf $(OBJ)

fclean: clean
	@echo "$(RED)removing $(NAME) executable$(RESET)"
	@rm -rf $(LIBFT)
	@rm -rf $(NAME)

re: fclean all
