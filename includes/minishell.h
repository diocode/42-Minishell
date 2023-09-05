/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:19:08 by digoncal          #+#    #+#             */
/*   Updated: 2023/07/24 12:29:59 by digoncal         ###   ########.fr       */
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

/*------------- Structures ---------------*/

typedef struct s_heredoc
{
	int	error_num;
	int	stop_heredoc;
	int	in_process;
	int	in_heredoc;
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
	pid_t			pid;
	int				flg[2];
	int
}	t_prompt;

enum	e_errors
{
	FORKERR = 8,
};

/*---------- FUNCTIONS ----------*/

//init
t_prompt		*init_prompt(char **av, char **ev);
t_simple_cmds	*init_simple_cmds(void);

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
void			execute(t_prompt *prompt);
void			handle_cmd(t_prompt *prompt, int process);
void			replace_variables(t_prompt *prompt, t_simple_cmds *process);

//heredoc
int				send_heredoc(t_prompt *prompt, t_simple_cmds *process);

//trim_input
char			**trim_input(t_prompt *prompt, char *input);
void			check_flg(t_prompt *p, char const *str, int i);
int				qts_nbr(t_prompt *prompt, char const *str, int i, int size);
int				skip_word(t_prompt *prompt, char const *str, int i);

//utils
char			**dup_arr(char **arr);
char			**extend_arr(char **arr, char *new);
void			ms_error(int err, int status, char *param);
int				is_whitespace(char c);

//signal
void			handle_sign(int sig, siginfo_t *info, void *c);
void			set_sign(void);

//lists
t_lexer			*ms_lstnew(char *content, char type);
void			ms_lstadd(t_lexer *lst, t_lexer *new);
void			ms_delnode(t_lexer *node);
t_lexer			*ms_lstlast(t_lexer *lst);

//free
t_prompt		*reset_prompt(t_prompt *prompt, char **av, char **ev);
void			free_data(t_prompt *prompt);
void			free_array(char **arr);
void			free_lexer(t_lexer *lst);
void			free_parser(t_simple_cmds *simple_cmds);

//builtins
void			add_new_path(t_prompt *prompt);
void			ms_env(t_prompt *prompt);
int				ms_cd(t_prompt *prompt, t_simple_cmds *simple_cmds);
void			exit_env(t_prompt *prompt);

#endif