/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:52:14 by digoncal          #+#    #+#             */
/*   Updated: 2023/05/29 19:13:00 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ---------- LIBRARIES ---------- */

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

/*------------- Strutures ---------------*/

typedef struct s_info
{
	char	**env;
	char	*args;
	char	*pwd;
	char	*old_pwd;
	int		*pid;
}	t_info;

/*---------- FUNCTIONS ----------*/

void	find_pwd(t_info *info);
t_info	*init_info(char **ev);
void	reset_env(t_info *info);
void	setup_env(t_info *info);
int		ms_loop(t_info *info);

//utils
char	**dup_arr(char **arr);


//free
void	free_info(t_info *info);
void	free_array(char **arr);

#endif