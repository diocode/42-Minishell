/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:29:47 by digoncal          #+#    #+#             */
/*   Updated: 2023/09/10 16:05:08 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

t_prompt	*reset_prompt(t_prompt *prompt, char **av, char **ev)
{
	t_prompt	*reset;

	free_data(prompt);
	reset = init_prompt(av, ev);
	reset->reset = true;
	return (reset);
}

void	free_lexer(t_lexer *lst)
{
	t_lexer	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		if (lst->str)
			free(lst->str);
		if (lst->token)
			free(lst->token);
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

void	free_parser(t_simple_cmds *simple_cmds)
{
	t_simple_cmds	*tmp;

	if (!simple_cmds)
		return ;
	while (simple_cmds)
	{
		if (simple_cmds->str)
			free_array(simple_cmds->str);
		if (simple_cmds->builtin)
			free(simple_cmds->builtin);
		if (simple_cmds->hd_file)
			free(simple_cmds->hd_file);
		if (simple_cmds->redirct)
			free_lexer(simple_cmds->redirct);
		tmp = simple_cmds;
		simple_cmds = simple_cmds->next;
		free(tmp);
	}
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_data(t_prompt *prompt)
{
	if (!prompt)
		return ;
	if (prompt->lexer)
		free_lexer(prompt->lexer);
	if (prompt->simple_cmds)
		free_parser(prompt->simple_cmds);
	if (prompt->env)
		free_array(prompt->env);
	if (prompt->pid)
		free(prompt->pid);
	free(prompt);
}
