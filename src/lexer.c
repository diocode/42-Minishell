/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:14:26 by digoncal          #+#    #+#             */
/*   Updated: 2023/07/04 17:35:12 by digoncal         ###   ########.fr       */
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
	if (!str)
		return (0);
	if ((str[0] == '|' || str[0] == '<' || str[0] == '>')
		&& ft_strlen(str) == 1)
		return (1);
	if ((ft_strncmp(str, "<<", 2) == 0 || ft_strncmp(str, ">>", 2) == 0)
		&& ft_strlen(str) == 2)
		return (1);
	return (0);
}

static int	init_lst(t_prompt *prompt, char **cmds, int i)
{
	while (cmds[++i])
	{
		if (is_token(cmds[i]))
		{
			*prompt->lexer = ms_lstnew(cmds[i], 't');
			break ;
		}
		else if (cmds[i][0])
		{
			*prompt->lexer = ms_lstnew(cmds[i], 'w');
			break ;
		}
	}
	return (i);
}

void	lexer(t_prompt *prompt, char *input)
{
	char		**cmds;
	int			i;

	if (!input[0])
	{
		*prompt->lexer = NULL;
		return ;
	}
	input = check_quotes(input);
	printf("INPUT: %s\n", input);
	cmds = trim_input(prompt, input);
	if (!cmds)
		return ;
	i = init_lst(prompt, cmds, -1);
	while (cmds[++i])
	{
		if (is_token(cmds[i]))
			ms_lstadd(prompt->lexer, ms_lstnew(cmds[i], 't'));
		else if (cmds[i][0])
			ms_lstadd(prompt->lexer, ms_lstnew(cmds[i], 'w'));
	}
}
