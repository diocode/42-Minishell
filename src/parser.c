/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:07:35 by digoncal          #+#    #+#             */
/*   Updated: 2023/07/23 13:27:06 by logname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	if_words(t_prompt *prompt, t_simple_cmds *cmds)
{
	int	size;

	if (prompt->lexer && prompt->lexer->str)
	{
		size = nbr_nodes(prompt->lexer);
		if (!cmds->str)
		{
			prompt->flg[0] = 0;
			cmds->str = malloc((size + 1) * sizeof(char *));
			cmds->str[size] = NULL;
			cmds->str[prompt->flg[0]] = ft_strdup(prompt->lexer->str);
		}
		else
			cmds->str[prompt->flg[0]] = ft_strdup(prompt->lexer->str);
		prompt->lexer = prompt->lexer->next;
		prompt->flg[0]++;
	}
}

static void	if_redirct(t_prompt *prompt, t_simple_cmds *cmds)
{
	t_lexer			*tmp;

	if (prompt->lexer && is_redirct(prompt->lexer->token))
	{
		cmds->num_redirct++;
		cmds->redirct = ft_strdup(prompt->lexer->token);
		tmp = prompt->lexer;
		prompt->lexer = prompt->lexer->next;
		ms_delnode(tmp);
		if (prompt->lexer && prompt->lexer->str)
		{
			cmds->file = ft_strdup(prompt->lexer->str);
			tmp = prompt->lexer;
			prompt->lexer = prompt->lexer->next;
			ms_delnode(tmp);
		}
	}
}

static void	get_simple_cmds(t_prompt *prompt, int pipes)
{
	t_simple_cmds	*cmds;
	t_simple_cmds	*tmp_cmds;
	t_lexer			*tmp;

	cmds = prompt->simple_cmds;
	tmp = prompt->lexer;
	while (prompt->lexer && pipes >= 0)
	{
		if (prompt->lexer->token && !ft_strncmp(prompt->lexer->token, "|", 1))
		{
			pipes--;
			prompt->lexer = prompt->lexer->next;
			tmp_cmds = init_simple_cmds();
			if (!tmp_cmds)
				return ;
			cmds->next = tmp_cmds;
			tmp_cmds->prev = cmds;
			cmds = cmds->next;
		}
		if_redirct(prompt, cmds);
		if (prompt->lexer && is_builtin(prompt->lexer->str) && !cmds->builtin)
			cmds->builtin = ft_strdup(prompt->lexer->str);
		if_words(prompt, cmds);
	}
	prompt->lexer = tmp;
}

void	parser(t_prompt *prompt)
{
	t_lexer		*lexer;
	int			pipes;

	lexer = prompt->lexer;
	pipes = 0;
	while (lexer)
	{
		if (lexer->token && !ft_strncmp(lexer->token, "|", 1))
			pipes++;
		lexer = lexer->next;
	}
	get_simple_cmds(prompt, pipes);
	if (!prompt->simple_cmds)
		return ;
}
