/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:07:35 by digoncal          #+#    #+#             */
/*   Updated: 2023/06/28 13:55:42 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*

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

static void	get_simple_cmds(t_prompt *prompt, int pipes)
{
	t_lexer			*lexer;

	lexer = *prompt->lexer;
	while (lexer)
	{
		while (pipes >= 0 && ft_strncmp(lexer->token, "|", 1))
		{
			if (is_redirct(lexer->token))
			{
				if (!redd)
				redirct = malloc(sizeof(t_lexer));
				if (!redirct)
					return ;
			}
			lexer = lexer->next;
		}
		pipes--;
	}
	*//*PARSE THROUGH THE LEXER UNTIL YOU FIND A PIPE*//*
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
}

 */
