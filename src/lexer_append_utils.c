/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_append_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 17:54:15 by digoncal          #+#    #+#             */
/*   Updated: 2023/12/19 18:26:50 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

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

static int	handle_quotes(t_prompt *p, char *input, size_t *i)
{
	while (input[*i] && input[*i] != '$' && ((input[*i] >= 'A'
				&& input[*i] <= 'Z') || (input[*i] >= 'a' && input[*i] <= 'z')))
	{
		if (is_quote(input[*i]))
		{
			if (!skip_quotes(input, i))
			{
				p->no_node = true;
				return (1);
			}
		}
		*i += 1;
	}
	return (0);
}

int	handle_word(t_prompt *p, char **str, char *input, char *val)
{
	char	*value;
	size_t	i;

	i = 1;
	if (handle_quotes(p, input, &i))
		return (quotes_error(input[i]), 1);
	value = ft_substr(input, 1, i - 1);
	if (!value)
	{
		p->no_node = true;
		return (1);
	}
	val = ms_getenv(value, p->env);
	if (!val)
	{
		p->no_node = true;
		return (*str += i, 0);
	}
	*str += add_node(p, val, (int)i, ft_strlen(val));
	free(value);
	free(val);
	return (0);
}
