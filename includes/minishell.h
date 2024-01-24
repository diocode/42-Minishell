/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:19:08 by digoncal          #+#    #+#             */
/*   Updated: 2023/11/21 13:28:37 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ---------- LIBRARIES ---------- */

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <sys/stat.h>

/*------------- Structures ---------------*/

typedef enum s_type
{
	OTHER,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	REDIR2_OUT,
}	t_type;

typedef struct s_token
{
	char			*content;
	t_type			type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_process
{
	char				**args;
	char				*builtin;
	t_token				*redirct;
	char				*hd_file;
	struct s_process	*next;
	struct s_process	*prev;
}	t_process;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	char			*input;
	t_env			*env;
	t_token			*lexer;
	t_process		*process;
	pid_t			pid;
	bool			interact;
	bool			quote[2];
}	t_shell;

/*---------- FUNCTIONS ----------*/

t_shell	*ms(void);
void	parser(void);

//lexer
void	lexer(char *input);
t_type	get_type(char *word);

//expander
void	expander(void);
int		expand_str(t_token *lx, size_t i);

//init
void	init(char **av, char **ev);

//env
void	ms_setenv(char *key, char *value);
char	*ms_getenv(char *key);
void	print_env(void);

//builtins
int		ms_exit(t_process *process);

//signals
void	set_signals(void);

//error
void	ms_error(int error);
int		redirection_error(void);
int		token_error(void);
int		pipe_error(void);

//free
void	free_data(bool reset);
void	free_array(char **arr);

//utils
char	**dup_arr(char **arr);
void	skip_spaces(char **line);
int		is_whitespace(char c);
int		is_digit(char *str);
bool	valid_quotes(char *str);
bool	in_quotes(char c);
int		count_pipes(t_token *lx);
bool	is_redirect(char *str);
bool	is_operator(char *str);

#endif