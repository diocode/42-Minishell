/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:19:08 by digoncal          #+#    #+#             */
/*   Updated: 2023/07/12 18:23:35 by digoncal         ###   ########.fr       */
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

/*------------- Structures ---------------*/

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
	char					*file;
	char					*redirct;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;

typedef struct s_prompt
{
	t_lexer			*lexer;
	t_simple_cmds	*simple_cmds;
	char			**env;
	pid_t			pid;
	int				flg[2];
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
void			lexer(t_prompt *prompt, char *input);

//parser
void			parser(t_prompt *prompt);

//trim_input
char			**trim_input(t_prompt *prompt, char *input);

//trim_input
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
t_prompt		*reset_prompt(t_prompt *prompt, char **av, char **ev);

//free
void			free_data(t_prompt *prompt);
void			free_array(char **arr);
void			free_lexer(t_lexer *lst);
void			free_parser(t_simple_cmds *simple_cmds);

//builtins
void			execute_builtin(t_prompt *prompt);
void			ms_env(t_prompt *prompt);
void			ms_pwd(t_prompt *prompt);
void			ms_cd(t_prompt *prompt);
/*void			ms_echo(t_prompt *prompt);
void			ms_export(t_prompt *prompt);
int				ms_unset(t_prompt *prompt);
*/
#endif