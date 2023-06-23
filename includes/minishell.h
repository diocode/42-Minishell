/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:52:14 by digoncal          #+#    #+#             */
/*   Updated: 2023/06/22 13:47:00 by digoncal         ###   ########.fr       */
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

typedef struct s_prompt
{
	t_lexer	**lexer;
	char	**env;
	pid_t	pid;
}			t_prompt;

enum	e_errors
{
	FORKERR = 8,
};

/*---------- FUNCTIONS ----------*/

//init
t_prompt	*init_prompt(char **av, char **ev);

//env
char		**ms_setenv(char *var, char *value, char **env);
char		*ms_getenv(char *var, char **env);

//lexer
void		lexer(t_prompt *prompt, char *input);

//cdmtrim
char		**trim_input(char *input);

//utils
char		**dup_arr(char **arr);
char		**extend_arr(char **arr, char *new);
void		ms_error(int err, int status, char *param);

//signal
void		handle_sign(int sig, siginfo_t *info, void *c);
void		set_sign(void);

//lists
t_lexer		*ms_lstnew(char *content, char type);
void		ms_lstadd(t_lexer **lst, t_lexer *new);

//free
void		free_data(t_prompt *prompt);
void		free_array(char **arr);
void		free_lexer(t_lexer **lst);

//builtins
void		execute_builtin(t_prompt *prompt);
void		ms_env(t_prompt *prompt);
void		ms_pwd(t_prompt *prompt);
void		ms_cd(t_prompt *prompt);
/*void		ms_echo(t_prompt *prompt);
void		ms_export(t_prompt *prompt);
int			ms_unset(t_prompt *prompt);
void		ms_exit_builtins(t_prompt *prompt);*/

#endif