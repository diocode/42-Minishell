/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:29:47 by digoncal          #+#    #+#             */
/*   Updated: 2023/10/24 14:35:18 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		{
			unlink(simple_cmds->hd_file);
			free(simple_cmds->hd_file);
		}
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

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
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
	if (prompt->heredoc)
		free(prompt->heredoc);
	if (prompt->env)
		free_array(prompt->env);
	if (prompt->pid)
		free(prompt->pid);
	if (prompt->exit_codes)
		free(prompt->exit_codes);
	free(prompt);
}
