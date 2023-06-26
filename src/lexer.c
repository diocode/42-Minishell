/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:14:26 by digoncal          #+#    #+#             */
/*   Updated: 2023/06/22 16:42:55 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_quotes(char const *str)
{
	int	i;
	int	total_quotes;

	i = -1;
	total_quotes = 0;
	while (str[++i])
		if (str[i] == '"')
			total_quotes++;
	if (total_quotes % 2 != 0)
	{
		printf("syntax error: looking for matching \'\"\'\n");
		return (1);
	}
	return (0);
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

void	lexer(t_prompt *prompt, char *input)
{
	char		**cmds;
	int			i;

	if (!input[0])
	{
		*prompt->lexer = NULL;
		return ;
	}
	if (check_quotes(input))
		return ;
	cmds = trim_input(input);
	if (!cmds)
		return ;
	if (is_token(cmds[0]))
		*prompt->lexer = ms_lstnew(cmds[0], 't');
	else
		*prompt->lexer = ms_lstnew(cmds[0], 'w');
	i = 0;
	while (cmds[++i])
	{
		if (is_token(cmds[i]))
			ms_lstadd(prompt->lexer, ms_lstnew(cmds[i], 't'));
		else
			ms_lstadd(prompt->lexer, ms_lstnew(cmds[i], 'w'));
	}
}
