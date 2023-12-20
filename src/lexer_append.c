/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:49:19 by digoncal          #+#    #+#             */
/*   Updated: 2023/12/20 13:20:40 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

static char	*iden_redict(char *str)
{
	char	*value;
	int		i;

	i = -1;
	while (str[++i])
		if (is_whitespace(str[i]))
			break ;
	value = ft_substr(str, 0, i);
	return (value);
}

static int	iden_util(t_prompt *prompt, char **str, char *value, size_t	*i)
{
	if (prompt->redict_flg)
	{
		value = iden_redict(*str);
		*i = ft_strlen(value);
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

int	append_identifier(t_prompt *prompt, char **str)
{
	char	*tmp;
	char	*value;
	size_t	i;

	value = NULL;
	tmp = *str;
	i = -1;
	while (tmp[++i] && !is_separator(tmp + i) && (tmp[i] != '$'
			|| (tmp[i] == '$' && tmp[i + 1] == '?')))
	{
		if (is_quote(tmp[i]))
		{
			if (!skip_quotes(tmp, &i))
				return (quotes_error(tmp[i]), 1);
			break ;
		}
	}
	if (iden_util(prompt, str, value, &i))
		return (1);
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
	char	*input;
	char	*val;

	val = NULL;
	input = *str;
	if (is_whitespace(input[1]) || !ft_strncmp(input, "$", 2))
		*str += add_node(prompt, input, 1, 1);
	else if (!ft_strncmp(input, "$$", 2))
	{
		val = ms_getenv("SYSTEMD_EXEC_PID", prompt->env);
		*str += add_node(prompt, val, 2, ft_strlen(val));
		free(val);
	}
	else if (ft_isdigit(input[1]))
		doll_sign_digit(prompt, str);
	else if (input[1] == '?')
	{
		val = ft_itoa(g_status);
		*str += add_node(prompt, val, 2, ft_strlen(val));
		free(val);
	}
	else
		return (handle_word(prompt, str, input, val));
	return (0);
}
