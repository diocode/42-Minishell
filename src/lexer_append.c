/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:49:19 by digoncal          #+#    #+#             */
/*   Updated: 2023/11/30 19:41:26 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

int	append_identifier(t_prompt *prompt, char **str)
{
	char	*tmp;
	char	*value;
	size_t	i;

	i = -1;
	tmp = *str;
	while (tmp[++i] && !is_separator(tmp + i) && (tmp[i] != '$' || (tmp[i] == '$' && tmp[i + 1] == '?')))
	{
		if (is_quote(tmp[i]))
		{
			if (!skip_quotes(tmp, &i))
				return (quotes_error(tmp[i]), 1);
		}
	}
	value = ft_substr(tmp, 0, i);
	if (!value)
		return (1);
	remove_quotes(value);
	if (!prompt->lexer)
		prompt->lexer = ms_lstnew(value, 'w');
	else
		ms_lstadd(prompt->lexer, ms_lstnew(value, 'w'));
	*str += i;
	free(value);
	return (0);
}

int	append_separator(t_prompt *prompt, char *token, char **line)
{
	if (!prompt->lexer)
		prompt->lexer = ms_lstnew(token, 't');
	else
		ms_lstadd(prompt->lexer, ms_lstnew(token, 't'));
	*line += 1;
	if (!ft_strncmp(token, "<<", 3) || !ft_strncmp(token, ">>", 3))
		*line += 1;
	return (0);
}

int	append_doll_sign(t_prompt *prompt, char **str)
{
	char	*tmp1;
	char	*tmp2;
	char	*value;
	size_t	i;

	tmp1 = *str;
	if (ft_isdigit(tmp1[1]))
	{
		*str += 2;
		return (0);
	}
	if (tmp1[1] == '?')
	{
		if (!prompt->lexer)
			prompt->lexer = ms_lstnew(ft_itoa(g_status), 'w');
		else
			ms_lstadd(prompt->lexer, ms_lstnew(ft_itoa(g_status), 'w'));
		*str += 2;
		return (0);
	}
	i = 1;
	while (tmp1[i] && tmp1[i] != '$')
	{
		if (is_quote(tmp1[i]))
		{
			if (!skip_quotes(tmp1, &i))
				return (quotes_error(tmp1[i]), 1);
		}
		i++;
	}
	value = ft_substr(tmp1, 1, i - 1);
	if (!value)
		return (1);
	tmp2 = ms_getenv(value, prompt->env);
	if (!tmp2)
	{
		*str += i;
		return (0);
	}
	if (!prompt->lexer)
		prompt->lexer = ms_lstnew(tmp2, 'w');
	else
		ms_lstadd(prompt->lexer, ms_lstnew(tmp2, 'w'));
	*str += i;
	free(value);
	free(tmp2);
	return (0);
}
