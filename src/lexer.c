/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:14:26 by digoncal          #+#    #+#             */
/*   Updated: 2023/07/14 16:34:15 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* flg[0] = '"' | flg[1] = '\'' */
/*Adds a quote to the end of the str if the quotes are odd numbered*/
static char	*check_quotes(char *str)
{
	int	flg[2];
	int	i;

	flg[0] = 0;
	flg[1] = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '"')
			flg[0]++;
		if (str[i] == '\'')
			flg[1]++;
	}
	if (flg[0] % 2 || flg[1] % 2)
	{
		if (flg[0] % 2)
			return (ft_strjoin(str, "\""));
		else
			return (ft_strjoin(str, "\'"));
	}
	return (str);
}

static int	is_token(char *str)
{
	if (!str || !str[0])
		return (0);
	if ((str[0] == '|' || str[0] == '<' || str[0] == '>')
		&& ft_strlen(str) == 1)
		return (1);
	if ((ft_strncmp(str, "<<", 2) == 0 || ft_strncmp(str, ">>", 2) == 0)
		&& ft_strlen(str) == 2)
		return (1);
	return (0);
}

static void	gen_lexer(t_prompt *prompt, char *cmd)
{
	if (is_token(cmd))
	{
		if (!prompt->lexer)
			prompt->lexer = ms_lstnew(cmd, 't');
		else
			ms_lstadd(prompt->lexer, ms_lstnew(cmd, 't'));
	}
	else if (cmd[0])
	{
		if (!prompt->lexer)
			prompt->lexer = ms_lstnew(cmd, 'w');
		else
			ms_lstadd(prompt->lexer, ms_lstnew(cmd, 'w'));
	}
}

int	lexer(t_prompt *prompt, char *input)
{
	char		**cmds;
	int			i;

	if (!input[0])
		return (0);
	input = check_quotes(input);
	cmds = trim_input(prompt, input);
	if (!cmds)
		return (0);
	i = -1;
	while (cmds[++i])
		gen_lexer(prompt, cmds[i]);
	return (1);
}
