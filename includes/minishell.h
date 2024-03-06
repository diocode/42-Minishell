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
	t_token				*redirect;
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
	int				*pid;
	bool			interact;
	bool			heredoc;
	bool			reset;
	bool			quote[2];
}	t_shell;

/*---------- FUNCTIONS ----------*/

t_shell	*ms(void);

//lexer
void	lexer(char *input);
t_type	get_type(char *word);

//expander
int		expander(void);
int		expand_str(t_token *lx, size_t i);

//parser
int		parser(void);
void	trim_quotes(void);
char	**get_args(void);

//execute
void	execute(void);
void	single_cmd(t_process *process);
int		handle_cmd(t_process *process);
int		system_cmd(t_process *process);
char	**get_paths(void);

//env
void	ms_setenv(char *key, char *value);
char	*ms_getenv(char *key);
t_env	*copy_env(t_env *env);
t_env	*create_node(char *key, char *value);

//builtins
int		builtin(t_process *process);
int		ms_exit(t_process *process);
int		ms_cd(t_process *process);
int		ms_env(bool export);
int		ms_pwd(void);
int		ms_export(t_process *process);
int		ms_unset(t_process *process);
int		ms_echo(t_process *process);
bool	existing_key(t_env	*env, char *str);

//heredoc
int		send_heredoc(t_process *process);
char	*expand_heredoc(char *input);

//redirect
int		setup_redirect(t_process *process);

//signals
void	set_signals(void);

//error
void	ms_error(int error);
int		redirection_error(void);
int		token_error(void);
int		pipe_error(void);
int		export_error(char *c);
int		error_cmd_not_found(t_process *process);

//init
void	init(char **av, char **ev);
int		init_pid(void);

//free
void	free_data(bool reset);
void	free_array(char **arr);
void	free_env(t_env *tmp);

//utils
char	**dup_arr(char **arr);
char	*clean_quotes(char *str, char c);
void	skip_spaces(char **line);
bool	valid_quotes(char *str);
int		count_pipes(t_token *lx);
int		equal_sign(const char *str);
int		is_whitespace(char c);
int		is_digit(char *str);
int		is_identifier(char c);
bool	in_quotes(char c);
bool	is_operator(char *str);
bool	is_builtin(char *str);
char	**list_to_array(t_env *list);
bool	solo_doll_sign(const char *str);
int		array_len(char **array);

#endif