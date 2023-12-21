/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:52:17 by digoncal          #+#    #+#             */
/*   Updated: 2023/12/21 16:52:17 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_reset(t_prompt *prompt, char **av, char **ev)
{
	char		*path;

	path = NULL;
	prompt->lexer = NULL;
	prompt->simple_cmds = NULL;
	prompt->heredoc = NULL;
	init_flags(prompt);
	prompt->pid = NULL;
	prompt->exit_codes = NULL;
	prompt->env = dup_arr(ev);
	init_vars(prompt, av, path);
}

static void	reset_data(t_prompt *prompt)
{
	if (!prompt)
		return ;
	if (prompt->lexer)
		free_lexer(prompt->lexer);
	if (prompt->simple_cmds)
		free_parser(prompt->simple_cmds);
	if (prompt->heredoc)
		free(prompt->heredoc);
	if (prompt->env)
		free_array(prompt->env);
	if (prompt->pid)
		free(prompt->pid);
	if (prompt->exit_codes)
		free(prompt->exit_codes);
	prompt = NULL;
}

void	reset_prompt(t_prompt *prompt, char **av, char **ev)
{
	char		**old_env;

	old_env = dup_arr(prompt->env);
	reset_data(prompt);
	init_reset(prompt, av, ev);
	prompt->reset = true;
	if (prompt->env)
	{
		free_array(prompt->env);
		prompt->env = old_env;
	}
	else
		free_array(old_env);
}
