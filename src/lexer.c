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

static int	append_identifier(t_prompt *prompt, char **str)
{
	char	*tmp;
	char	*value;
	size_t	i;

	i = -1;
	tmp = *str;
	while (tmp[++i] && !is_separator(tmp + i))
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

static int	append_separator(t_prompt *prompt, char *token, char **line)
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

static int	handle_separator(t_prompt *prompt, char **line_ptr)
{
	if (!ft_strncmp(*line_ptr, "<<", 2))
		return (append_separator(prompt, "<<", line_ptr));
	else if (!ft_strncmp(*line_ptr, ">>", 2))
		return (append_separator(prompt, ">>", line_ptr));
	else if (!ft_strncmp(*line_ptr, "<", 1))
		return (append_separator(prompt, "<", line_ptr));
	else if (!ft_strncmp(*line_ptr, ">", 1))
		return (append_separator(prompt, ">", line_ptr));
	else if (!ft_strncmp(*line_ptr, "|", 1))
		return (append_separator(prompt, "|", line_ptr));
	else
		return (1);
}

static int	handle_tokenize(t_prompt *prompt, char *str)
{
	int		error;

	error = 0;
	while (*str)
	{
		if (error)
			return (free_lexer(prompt->lexer), 1);
		if (is_whitespace(*str))
			skip_spaces(&str);
		else if (!ft_strncmp(str, "<", 1) || !ft_strncmp(str, ">", 1)
			|| !ft_strncmp(str, "|", 1))
			error = (handle_separator(prompt, &str));
		else
			error = (append_identifier(prompt, &str));
	}
	return (0);
}

int	lexer(t_prompt *prompt, char *input)
{
	if (!input[0])
		return (1);
	handle_tokenize(prompt, input);
	free(input);
	if (!prompt->lexer)
		return (1);
	return (0);
}
