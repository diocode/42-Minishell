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

int	append_identifier(t_prompt *prompt, char **str, size_t	i)
{
	char	*tmp;
	char	*value;

	tmp = *str;
	while (tmp[++i] && !is_separator(tmp + i) && (tmp[i] != '$'
			|| (tmp[i] == '$' && tmp[i + 1] == '?')))
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

static int	add_node(t_prompt *prompt, char *str, int index)
{
	if (!prompt->lexer)
		prompt->lexer = ms_lstnew(str, 'w');
	else
		ms_lstadd(prompt->lexer, ms_lstnew(str, 'w'));
	return (index);
}

static int	handle_word(t_prompt *prompt, char **str, char *input, char *env)
{
	char	*value;
	size_t	i;

	i = 1;
	while (input[i] && input[i] != '$')
	{
		if (is_quote(input[i]))
		{
			if (!skip_quotes(input, &i))
				return (quotes_error(input[i]), 1);
		}
		i++;
	}
	value = ft_substr(input, 1, i - 1);
	if (!value)
		return (1);
	env = ms_getenv(value, prompt->env);
	if (!env)
		return (*str += i, 0);
	*str += add_node(prompt, env, i);
	free(value);
	free(env);
	return (0);
}

int	append_doll_sign(t_prompt *prompt, char **str)
{
	char	*input;
	char	*env;

	env = NULL;
	input = *str;
	if (!ft_strncmp(input, "$", 2) && ft_strlen(input) == 1)
		*str += add_node(prompt, input, 1);
	else if (!ft_strncmp(input, "$$", 3) && ft_strlen(input) == 2)
	{
		env = ms_getenv("SYSTEMD_EXEC_PID", prompt->env);
		*str += add_node(prompt, env, 1);
		free(env);
	}
	else if (ft_isdigit(input[1]))
		*str += 2;
	else if (input[1] == '?')
		*str += add_node(prompt, ft_itoa(g_status), 2);
	else
		return (handle_word(prompt, str, input, env));
	return (0);
}
