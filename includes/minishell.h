/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:52:14 by digoncal          #+#    #+#             */
/*   Updated: 2023/05/31 16:06:27 by digoncal         ###   ########.fr       */
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

/*------------- Strutures ---------------*/

typedef struct s_prompt
{
	t_list	*cmds;
	char	**env;
	pid_t	pid;
}			t_prompt;

enum	e_errors
{
	FORKERR = 8,
};

/*---------- FUNCTIONS ----------*/

//parser
int		check_prompt(t_prompt *prompt, char *input);

//utils
char	**dup_arr(char **arr);
void	ms_error(int err, int status, char *param);
void	handle_sigint(int sig);

//signal
void	handle_sign(int sig);

//free
void	free_data(t_prompt *prompt);
void	free_array(char **arr);

#endif