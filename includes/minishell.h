/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:52:14 by digoncal          #+#    #+#             */
/*   Updated: 2023/06/19 20:07:16 by rpaiva-l         ###   ########.fr       */
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

typedef struct s_prompt
{
	char	*cmds;
	char	**env;
	pid_t	pid;
}			t_prompt;

typedef struct s_data
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
}			t_data;

enum	e_errors
{
	FORKERR = 8,
};

/*---------- FUNCTIONS ----------*/

//parser
int			check_prompt(t_prompt *prompt, char *input);

//init
t_prompt	*init_prompt(char **av, char **ev);

//env
char		**ms_setenv(char *var, char *value, char **env);
char		*ms_getenv(char *var, char **env);

//utils
char		**dup_arr(char **arr);
char		**extend_arr(char **arr, char *new);
void		ms_error(int err, int status, char *param);

//signal
void		handle_sign(int sig, siginfo_t *info, void *c);
void		set_sign(void);

//free
void		free_data(t_prompt *prompt);
void		free_array(char **arr);

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