/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:07:35 by digoncal          #+#    #+#             */
/*   Updated: 2023/07/06 18:00:01 by digoncal         ###   ########.fr       */
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
	if (ft_strncmp(str, "echo", 4) || ft_strncmp(str, "cd", 2)
		|| ft_strncmp(str, "pwd", 3) || ft_strncmp(str, "export", 6)
		|| ft_strncmp(str, "unset", 5) || ft_strncmp(str, "env", 3)
		|| ft_strncmp(str, "exit", 4))
		return (1);
	return (0);
}

static int	nbr_nodes(t_lexer *lexer)
{
	int	nodes;

	nodes = 0;
	while (lexer->str && !is_redirct(lexer->str)
		&& ft_strncmp(lexer->token, "|", 1))
	{
		nodes++;
		lexer = lexer->next;
	}
	return (nodes);
}

static t_simple_cmds	*init_simple_cmds(void)
{
	t_simple_cmds	*node;

	node = (t_simple_cmds *) malloc(sizeof(t_simple_cmds));
	if (!node)
		return (NULL);
	node->str = NULL;
	node->builtin = NULL;
	node->file = NULL;
	node->redirct = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

static void	get_simple_cmds(t_prompt *prompt, int pipes)
{
	t_lexer			*lexer;
	t_lexer			*tmp;
	t_simple_cmds	*cmds;
	int				i;

	lexer = *prompt->lexer;
	*prompt->simple_cmds = init_simple_cmds();
	cmds = *prompt->simple_cmds;
	cmds->num_redirct = 0;
	i = 0;
	while (lexer && pipes >= 0)
	{
		if (!ft_strncmp(lexer->token, "|", 1))
		{
			pipes--;
			cmds = cmds->next;
			lexer = lexer->next;
		}
		if (is_redirct(lexer->token))
		{
			cmds->num_redirct ++;
			if (!cmds->redirct)
				*cmds->redirct = ms_lstnew(lexer->token, 't');
			else
				ms_lstadd(cmds->redirct, ms_lstnew(lexer->token, 't'));
			tmp = lexer->next;
			ms_delnode(lexer);
			lexer = tmp;
			cmds->file = ft_strdup(lexer->str);
			if (lexer->str)
			{
				ms_lstadd(cmds->redirct, ms_lstnew(lexer->str, 'w'));
				tmp = lexer->next;
				ms_delnode(lexer);
				lexer = tmp;
			}
		}
		if (is_builtin(lexer->str))
			cmds->builtin = ft_strdup(lexer->str);
		if (lexer->str)
		{
			if (!cmds->str)
			{
				cmds->str = malloc((nbr_nodes(lexer) + 1) * sizeof(char *));
				cmds->str[nbr_nodes(lexer)] = NULL;
				cmds->str[0] = ft_strdup(lexer->str);
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

	lexer = *prompt->lexer;
	pipes = 0;
	while (lexer)
	{
		if (!ft_strncmp(lexer->token, "|", 1))
			pipes++;
		lexer = lexer->next;
	}
	get_simple_cmds(prompt, pipes);
	/*//test
	t_simple_cmds	*cmds = *prompt->simple_cmds;
	while (cmds)
	{
		printf("-----------\nSTR: ");
		for (int i = 0; cmds->str[i]; i++)
				printf("[%s] ", cmds->str[i]);
		printf("\n");
		printf("BUILTIN: %s", cmds->builtin);
		printf("REDIRCT NUMBER: %d", cmds->num_redirct);
		printf("REDIRCT: ");
		printf("FILE: %s\n", cmds->file);
		cmds = cmds->next;
	}*/
}
