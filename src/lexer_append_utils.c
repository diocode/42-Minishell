/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_append_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 17:54:15 by digoncal          #+#    #+#             */
/*   Updated: 2023/12/18 17:54:15 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

int	iden_util(t_prompt *prompt, char **str, char *value, size_t	*i)
{
	if (prompt->redict_flg)
	{
		value = ft_strdup(*str);
		*i = ft_strlen(*str);
	}
	else
	{
		value = ft_substr(*str, 0, *i);
		if (!value)
			return (1);
	}
	remove_quotes(value);
	if (!prompt->lexer)
		prompt->lexer = ms_lstnew(value, 'w');
	else
		ms_lstadd(prompt->lexer, ms_lstnew(value, 'w'));
	*str += *i;
	return (0);
}

void	doll_sign_digit(t_prompt *prompt, char **str)
{
	*str += 2;
	prompt->no_node = true;
}

int	add_node(t_prompt *prompt, char *str, int index, int len)
{
	char	*tmp;

	tmp = ft_substr(str, 0, len);
	if (!prompt->lexer)
		prompt->lexer = ms_lstnew(tmp, 'w');
	else
		ms_lstadd(prompt->lexer, ms_lstnew(tmp, 'w'));
	free(tmp);
	return (index);
}

int	handle_word(t_prompt *p, char **str, char *input, char *val)
{
	char	*value;
	size_t	i;

	i = 1;
	while (input[i] && input[i] != '$' && (input[i] >= 'A' && input[i] <= 'Z'))
	{
		if (is_quote(input[i]))
		{
			if (!skip_quotes(input, &i))
			{
				p->no_node = true;
				return (quotes_error(input[i]), 1);
			}
		}
		i++;
	}
	value = ft_substr(input, 1, i);
	if (!value)
	{
		p->no_node = true;
		return (1);
	}
	val = ms_getenv(value, p->env);
	if (!val)
	{
		if (p->merge)
		{
			p->no_node = true;
			return (*str += i, 0);
		}
		*str += add_node(p, input, ft_strlen(input), ft_strlen(input));
		free(value);
		return (0);
	}
	*str += add_node(p, val, (int)i, ft_strlen(val));
	free(value);
	free(val);
	return (0);
}