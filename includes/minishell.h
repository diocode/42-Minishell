/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:19:08 by digoncal          #+#    #+#             */
/*   Updated: 2023/09/09 13:01:07 by digoncal         ###   ########.fr       */
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

/*------------- Structures ---------------*/

typedef struct s_heredoc
{
	bool	status;
	int		error_num;
}	t_heredoc;

typedef struct s_lexer
{
	char			*str;
	char			*token;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_simple_cmds
{
	char					**str;
	char					*builtin;
	int						num_redirct;
	t_lexer					*redirct;
	char					*hd_file;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;

typedef struct s_prompt
{
	t_lexer			*lexer;
	t_simple_cmds	*simple_cmds;
	t_heredoc		*heredoc;
	char			**env;
	int				*pid;
	int				flg[2];
	bool			reset;
	bool			interact;
}	t_prompt;

/*---------- FUNCTIONS ----------*/

//init
t_prompt		*init_prompt(char **av, char **ev);
t_simple_cmds	*init_simple_cmds(void);
int				init_pid(t_prompt *prompt);

//env
char			**ms_setenv(char *var, char *value, char **env);
char			*ms_getenv(char *var, char **env);

//lexer
int				lexer(t_prompt *prompt, char *input);

//parser
void			parser(t_prompt *prompt);
int				is_redirct(char *str);
int				is_builtin(char const *str);
int				nbr_nodes(t_lexer *lexer);

//execute
int				execute(t_prompt *prompt);
int				handle_cmd(t_prompt *prompt, t_simple_cmds *cmd);
int				single_cmd(t_prompt *prompt, t_simple_cmds *process);
void			replace_variables(t_prompt *prompt, t_simple_cmds *process);

//heredoc
int				send_heredoc(t_prompt *prompt, t_simple_cmds *process);
t_simple_cmds	*single_cmd_heredoc(t_prompt *prompt, t_simple_cmds *process);

//redircts
int				setup_redirct(t_simple_cmds *process);

//str_expander
char			**single_cmd_expander(t_prompt *prompt, char **str);
char			*str_expander(t_prompt *prompt, char *str);
int				dollar_sign(char *str);
int				equal_sign(char *str);
char			*char_to_str(char c);
int				if_digit(char *str, int i);
int				if_question_mark(void);

//trim_input
char			**trim_input(t_prompt *prompt, char *input);
void			check_flg(t_prompt *p, char const *str, int i);
int				qts_nbr(t_prompt *prompt, char const *str, int i, int size);
int				skip_word(t_prompt *prompt, char const *str, int i);

//utils
char			**dup_arr(char **arr);
char			**extend_arr(char **arr, char *new);
int				is_whitespace(char c);
char			*delquotes(char *str, char c);
int				ms_error(int error);
int				error_cmd_not_found( t_simple_cmds *process);

//signal
void			execute_sig(int sig, void *prompt);
void			set_sign(void);

//lists
t_lexer			*ms_lstnew(char *content, char type);
void			ms_lstadd(t_lexer *lst, t_lexer *new);
t_lexer			*ms_lstlast(t_lexer *lst);

//free
t_prompt		*reset_prompt(t_prompt *prompt, char **av, char **ev);
void			free_data(t_prompt *prompt);
void			free_array(char **arr);
void			free_lexer(t_lexer *lst);
void			free_parser(t_simple_cmds *simple_cmds);

//builtins
int				ms_echo(t_simple_cmds *process);
void			ms_env(t_prompt *prompt, bool sort);
int				ms_cd(t_prompt *prompt, t_simple_cmds *simple_cmds);
int				ms_unset(t_prompt *prompt, t_simple_cmds *simple_cmds);
int				ms_export(t_prompt *prompt, t_simple_cmds *simple_cmds);
int				ms_exit(t_prompt *prompt, t_simple_cmds *simple_cmd);

//builtins_utils
int				export_error(char *c);
int				is_identifier(char c);
int				is_digit(char *str);

#endif