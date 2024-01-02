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
	int				*exit_codes;
	int				flg[3];
	bool			reset;
	bool			interact;
	bool			redict_flg;
	bool			merge;
	bool			no_node;
	bool			separator;
}	t_prompt;

/*---------- FUNCTIONS ----------*/

//init
t_prompt		*init_prompt(char **av, char **ev);
t_simple_cmds	*init_simple_cmds(void);
int				init_pid(t_prompt *prompt);
void			reset_prompt(t_prompt *prompt, char **av, char **ev);
void			init_flags(t_prompt *prompt);
void			init_vars(t_prompt *prompt, char **av, char *value);

//env
char			**ms_setenv(char *var, char *value, char **env);
char			*ms_getenv(char *var, char **env);

//lexer & utils
int				lexer(t_prompt *prompt, char *input);
void			skip_spaces(char **line);
int				is_separator(char *c);
int				is_quote(char c);
bool			skip_quotes(char *line, size_t *i);
void			remove_quotes(char *str);

//lexer_append && utils
int				append_identifier(t_prompt *prompt, char **str);
int				append_separator(t_prompt *prompt, char *token, char **line);
int				append_doll_sign(t_prompt *prompt, char **str);
int				add_node(t_prompt *prompt, char *str, int index, int len);
int				handle_word(t_prompt *p, char **str, char *input, char *val);
void			doll_sign_digit(t_prompt *prompt, char **str);

//parser
int				parser(t_prompt *prompt);
int				is_redirct(char *str);
int				is_builtin(char const *str);
int				nbr_nodes(t_lexer *lexer);

//execute
int				execute(t_prompt *prompt);
int				handle_cmd(t_prompt *prompt, t_simple_cmds *cmd);
int				single_cmd(t_prompt *prompt, t_simple_cmds *process);

//heredoc
t_simple_cmds	*single_cmd_heredoc(t_prompt *prompt, t_simple_cmds *process);
int				send_heredoc(t_prompt *prompt, t_simple_cmds *process);
int				init_heredoc(t_prompt *prompt);

//redircts
int				setup_redirct(t_simple_cmds *process);

//str_expander
char			**single_cmd_expander(t_prompt *prompt, char **str);
char			*str_expander(t_prompt *prompt, char *str);
char			*char_to_str(char c);
int				dol_sign(char *str);
int				equal_sign(char *str);
int				if_digit(char *str, int i);
int				if_question_mark(void);

//expand_input && utils
bool			is_expandable(const char *str);
bool			solo_doll_sign(const char *str);
char			*expand_input(t_prompt *prompt, char *input);
char			*get_env(t_prompt *p, char *val);

//utils_1
char			*delquotes(char *str, char c);
int				is_whitespace(char c);
int				is_identifier(char c);
int				is_digit(char *str);
void			init_exit_codes(t_prompt *prompt, char *input);

//utils_2
bool			is_exit_status(char *str);
int				current_exit_status(t_prompt *prompt);
int				check_param(char *str);
bool			existing_var(char *env, char *str);

//str_utils
char			**dup_arr(char **arr);
char			**extend_arr(char **arr, char *new);
char			*array_to_str(char **arr);

//errors
int				ms_error(int error);
int				export_error(char *c);
int				error_cmd_not_found( t_simple_cmds *process);
int				token_error(t_lexer *lexer);
void			quotes_error(char c);

//signal
void			execute_sig(int sig, void *prompt);
void			set_sign(void);

//lists
t_lexer			*ms_lstnew(char *content, char type);
t_lexer			*ms_lstlast(t_lexer *lst);
void			ms_lstadd(t_lexer *lst, t_lexer *new);
void			merge_nodes(t_prompt *prompt);

//free
void			free_data(t_prompt *prompt, bool reset);
void			reset_data(t_prompt *prompt);
void			free_array(char **arr);
void			free_lexer(t_lexer *lst);
void			free_parser(t_simple_cmds *simple_cmds);

//builtins
void			ms_env(t_prompt *prompt, bool sort);
int				ms_echo(t_prompt *prompt, t_simple_cmds *process);
int				ms_cd(t_prompt *prompt, t_simple_cmds *simple_cmds);
int				ms_unset(t_prompt *prompt, t_simple_cmds *simple_cmds);
int				ms_export(t_prompt *prompt, t_simple_cmds *simple_cmds);
int				ms_exit(t_prompt *prompt, t_simple_cmds *simple_cmd);
void			ms_pwd(t_prompt *prompt);

#endif