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

SRC = src/main.c src/init.c src/free.c src/signals.c src/utils.c src/error.c src/error_utils.c \
	src/is_utils.c src/str_utils.c src/array_utils.c src/system_cmd.c \
	src/expander_str.c src/trim_quotes.c src/heredoc.c src/expand_heredoc.c  src/redirects.c \
	src/env.c src/lexer.c src/parser.c src/expander.c src/execute.c src/cmds.c src/get_args.c \
	src/builtins/ms_exit.c src/builtins/ms_cd.c src/builtins/ms_export.c src/builtins/ms_env.c \
	src/builtins/ms_pwd.c src/builtins/ms_unset.c src/builtins/ms_echo.c

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
