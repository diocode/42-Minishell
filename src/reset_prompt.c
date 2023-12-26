/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:52:17 by digoncal          #+#    #+#             */
/*   Updated: 2023/12/21 16:52:17 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	reset_init(t_prompt *prompt, char **av, char **ev)
{
	char		*path;

	path = NULL;
	prompt->lexer = NULL;
	prompt->simple_cmds = NULL;
	prompt->heredoc = NULL;
	prompt->pid = NULL;
	prompt->exit_codes = NULL;
	init_flags(prompt);
	prompt->env = dup_arr(ev);
	init_vars(prompt, av, path);
}

void	reset_prompt(t_prompt *prompt, char **av, char **ev)
{
	char		**old_env;

	old_env = dup_arr(prompt->env);
	free_data(prompt, true);
	reset_init(prompt, av, ev);
	prompt->reset = true;
	if (prompt->env)
	{
		free_array(prompt->env);
		prompt->env = old_env;
	}
	else
		free_array(old_env);
}
