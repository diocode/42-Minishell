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

SRC = src/main.c src/utils_1.c src/free.c src/lexer.c src/signals.c src/init.c \
	src/env.c src/ms_lists.c src/parser.c src/lexer_utils.c src/parser_utils.c \
	src/execute.c src/expand_input.c src/expand_utils.c src/str_utils.c \
	src/builtins/ms_echo.c src/builtins/ms_cd.c src/errors.c src/lexer_append.c\
	src/heredoc.c src/str_expander.c src/str_expander_utils.c src/cmds.c \
	src/redircts.c src/builtins/ms_env.c src/builtins/ms_unset.c \
	src/builtins/ms_export.c src/builtins/ms_exit.c src/utils_2.c \
	src/lexer_append_utils.c src/merge_nodes.c src/reset_prompt.c \
	src/builtins/ms_pwd.c
OBJ = $(SRC:.c=.o)

LIBFT = libs/libft/libft.a

all: deps $(NAME)

deps:
	$(MAKE) -C ./libs/libft

$(NAME): $(OBJ) $(DEPS)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

clean:
	$(MAKE) $@ -C ./libs/libft
	@rm -rf $(OBJ)

fclean: clean
	$(MAKE) $@ -C ./libs/libft
	@rm -rf $(NAME)

re: fclean all
	$(MAKE) re -C ./libs/libft
