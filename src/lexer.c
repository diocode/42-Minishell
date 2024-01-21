/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:48:38 by digoncal          #+#    #+#             */
/*   Updated: 2024/01/18 17:48:38 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	in_quotes(char c)
{
	if (c == '\'' && !ms()->quote[1])
		ms()->quote[0] = !ms()->quote[0];
	else if (c == '\"' && !ms()->quote[0])
		ms()->quote[1] = !ms()->quote[1];
	return (ms()->quote[0] || ms()->quote[1]);
}

/* s_quotes = 0  |  d_quotes = 1 */
static size_t	word_len(char *input)
{
	size_t	len;

	len = 0;
	while (*input)
	{
		if (!in_quotes(*input) && is_whitespace(*input))
			break ;
		len++;
		input++;
	}
	return (len);
}

static void	add_lexer_node(char *word)
{
	t_token	*new;
	t_token	*tmp;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return ;
	new->content = word;
	new->type = 0;
	if (!ms()->lexer)
		ms()->lexer = new;
	else
	{
		tmp = ms()->lexer;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	lexer(char *input)
{
	char	*word;
	size_t	len;

	while (*input)
	{
		if (is_whitespace(*input))
			skip_spaces(&input);
		len = word_len(input);
		word = ft_substr(input, 0, len);
		add_lexer_node(word);
		input += len;
		if (*input)
			input++;
	}
}
