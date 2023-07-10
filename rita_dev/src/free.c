/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:29:47 by digoncal          #+#    #+#             */
/*   Updated: 2023/07/07 13:30:29 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

void	free_lexer(t_lexer **lst)
{
	t_lexer	*tmp;
	t_lexer	*node;

	node = (*lst);
	while (node)
	{
		tmp = node;
		node = node->next;
		free(tmp);
	}
	free(lst);
}

void	free_parser(t_simple_cmds **simple_cmds)
{
	t_simple_cmds	*cmds;

	if (!simple_cmds)
		return ;
	cmds = (*simple_cmds);
	while (cmds)
	{
		if (cmds->str)
			free_array(cmds->str);
		if (cmds->builtin)
			free(cmds->builtin);
		if (cmds->file)
			free(cmds->file);
		if (cmds->redirct)
			free(cmds->redirct);
		cmds = cmds->next;
		free(cmds->prev);
	}
	free(simple_cmds);
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
	free(prompt);
}
