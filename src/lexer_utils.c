/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:09:06 by digoncal          #+#    #+#             */
/*   Updated: 2023/11/30 15:09:06 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	skip_spaces(char **line)
{
	while (**line && is_whitespace(**line))
		(*line)++;
}

int	is_separator(char *c)
{
	if (*c == ' ' || *c == '\t' || *c == '|'
		|| *c == '>' || *c == '<')
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

bool	skip_quotes(char *line, size_t *i)
{
	char	quote;

	quote = line[*i];
	if (ft_strchr(line + *i + 1, quote))
	{
		(*i)++;
		while (line[*i] != quote)
			(*i)++;
		(*i)++;
		return (true);
	}
	return (false);
}

void	remove_quotes(char *str)
{
	size_t	i;
	size_t	j;
	char	quote;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			quote = str[i];
			i++;
			while (str[i] != quote)
				str[j++] = str[i++];
			i++;
		}
		else
			str[j++] = str[i++];
	}
	str[j] = '\0';
}
