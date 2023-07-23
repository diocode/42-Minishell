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

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
DEPS = libs/libft/libft.a

NAME = minishell
DEV = dev

SRC = src/main.c src/utils.c src/free.c src/lexer.c src/signals.c src/init.c \
	src/env.c src/builtins/builtins.c src/trim_input.c src/ms_lists.c \
	src/parser.c src/trim_input_utils.c src/parser_utils.c
OBJ = $(SRC:.c=.o)

SRC_DEV = src/dev.c src/utils.c src/free.c src/lexer.c src/signals.c src/init.c \
    src/env.c src/builtins/builtins.c src/trim_input.c src/ms_lists.c \
    src/parser.c src/trim_input_utils.c src/parser_utils.c
OBJ_DEV = $(SRC_DEV:.c=.o)

LIBFT = libs/libft/libft.a

all: deps $(NAME)

deps:
	$(MAKE) -C ./libs/libft

$(NAME): $(OBJ) $(DEPS)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

dev: deps $(DEV)

$(DEV): $(OBJ_DEV) $(DEPS)
	$(CC) $(CFLAGS) $(OBJ_DEV) $(LIBFT) -lreadline -o $(DEV)

clean:
	$(MAKE) $@ -C ./libs/libft
	@rm -rf $(OBJ)
	@rm -rf $(OBJ_DEV)

fclean: clean
	$(MAKE) $@ -C ./libs/libft
	@rm -rf $(NAME)
	@rm -rf $(DEV)

re: fclean all
	$(MAKE) re -C ./libs/libft
