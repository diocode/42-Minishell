/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:07:35 by digoncal          #+#    #+#             */
/*   Updated: 2023/07/22 19:11:47 by logname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_redirct(char *str)
{
	if (!str)
		return (0);
	if ((str[0] == '<' || str[0] == '>') && ft_strlen(str) == 1)
		return (1);
	if ((ft_strncmp(str, "<<", 2) == 0 || ft_strncmp(str, ">>", 2) == 0)
		&& ft_strlen(str) == 2)
		return (1);
	return (0);
}

static int	is_builtin(char const *str)
{
	if (!str)
		return (0);
	if (!ft_strncmp(str, "echo", 4) || !ft_strncmp(str, "cd", 2)
		|| !ft_strncmp(str, "pwd", 3) || !ft_strncmp(str, "export", 6)
		|| !ft_strncmp(str, "unset", 5) || !ft_strncmp(str, "env", 3)
		|| !ft_strncmp(str, "exit", 4))
		return (1);
	return (0);
}

static int	nbr_nodes(t_lexer *lexer)
{
	int			nodes;
	t_lexer		*node;

	nodes = 0;
	node = lexer;
	while (node && (node->str || node->token))
	{
		if (node->token && !ft_strncmp(node->token, "|", 1))
			return (nodes);
		if (is_redirct(node->token))
		{
			if (node->next && (node->next->str || node->next->token))
				node = node->next->next;
			else
				node = node->next;
		}
		else
		{
			nodes++;
			node = node->next;
		}
	}
	return (nodes);
}

/* i[0] - index | i[1] - flag for 1st pipe */
static void	get_simple_cmds(t_prompt *prompt, int pipes)
{
	t_lexer			*tmp;
	t_lexer			*lexer;
	t_simple_cmds	*cmds;
	t_simple_cmds	*tmp_cmds;
	int				i;

	lexer = prompt->lexer;
	cmds = prompt->simple_cmds;
	while (lexer && pipes >= 0)
	{
		if (lexer->token && !ft_strncmp(lexer->token, "|", 1))
		{
			pipes--;
			lexer = lexer->next;
			tmp_cmds = init_simple_cmds();
			if (!tmp_cmds)
				return ;
			cmds->next = tmp_cmds;
			tmp_cmds->prev = cmds;
			cmds = cmds->next;
		}
		if (lexer && is_redirct(lexer->token))
		{
			cmds->num_redirct ++;
			cmds->redirct = ft_strdup(lexer->token);
			tmp = lexer;
			lexer = lexer->next;
			ms_delnode(tmp);
			if (lexer && lexer->str)
			{
				cmds->file = ft_strdup(lexer->str);
				tmp = lexer;
				lexer = lexer->next;
				ms_delnode(tmp);
			}
		}
		if (lexer && is_builtin(lexer->str) && !cmds->builtin)
			cmds->builtin = ft_strdup(lexer->str);
		if (lexer && lexer->str)
		{
			if (!cmds->str)
			{
				i = 0;
				cmds->str = malloc((nbr_nodes(lexer) + 1) * sizeof(char *));
				cmds->str[nbr_nodes(lexer)] = NULL;
				cmds->str[i] = ft_strdup(lexer->str);

			}
			else
				cmds->str[i] = ft_strdup(lexer->str);
			lexer = lexer->next;
			i++;
		}
	}
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
