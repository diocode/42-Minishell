/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:08:13 by digoncal          #+#    #+#             */
/*   Updated: 2023/07/23 13:08:13 by logname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_redirct(char *str)
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

int	is_builtin(char const *str)
{
	if (!str)
		return (0);
	if (!ft_strncmp(str, "echo", 5) || !ft_strncmp(str, "cd", 3)
		|| !ft_strncmp(str, "pwd", 4) || !ft_strncmp(str, "export", 7)
		|| !ft_strncmp(str, "unset", 6) || !ft_strncmp(str, "env", 4)
		|| !ft_strncmp(str, "exit", 5))
		return (1);
	return (0);
}

int	nbr_nodes(t_lexer *lexer)
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
