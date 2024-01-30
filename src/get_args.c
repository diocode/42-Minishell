/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 01:28:14 by digoncal          #+#    #+#             */
/*   Updated: 2024/01/30 01:28:14 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_code;

static char	**new_args(void)
{
	t_token	*tmp;
	char	**args;
	size_t	i;

	tmp = ms()->lexer;
	i = 0;
	while (tmp && tmp->type == OTHER)
	{
		if (tmp->content[0])
			i++;
		tmp = tmp->next;
	}
	args = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (args && ms()->lexer && ms()->lexer->type == OTHER)
	{
		if (ms()->lexer->content[0])
		{
			args[++i] = ft_strdup(ms()->lexer->content);
			if (!args[i])
				return (g_exit_code = 1, free_array(args), ms_exit(NULL), NULL);
		}
		ms()->lexer = ms()->lexer->next;
	}
	return (args);
}

static size_t	get_size(void)
{
	t_token	*tmp;
	size_t	i;

	tmp = ms()->lexer;
	i = 0;
	while (tmp && tmp->type == OTHER)
	{
		if (tmp->content[0])
			i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**get_args(void)
{
	char	**args;
	size_t	i;

	if (!ms()->process->args)
		return (new_args());
	i = get_size();
	args = ft_calloc(i + array_len(ms()->process->args) + 1, sizeof(char *));
	i = -1;
	while (args && ms()->process->args[++i])
		args[i] = ft_strdup(ms()->process->args[i]);
	while (args && ms()->lexer && ms()->lexer->type == OTHER)
	{
		if (ms()->lexer->content[0])
		{
			args[i] = ft_strdup(ms()->lexer->content);
			if (!args[i])
				return (g_exit_code = 1, free_array(args), ms_exit(NULL), NULL);
			i++;
		}
		ms()->lexer = ms()->lexer->next;
	}
	free_array(ms()->process->args);
	return (args);
}
