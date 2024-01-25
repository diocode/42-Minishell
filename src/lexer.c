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

static size_t	operator_size(const char *str)
{
	if (!str && *str)
		return (0);
	if (*str == '|')
	{
		if (*(str + 1) != '|')
			return (1);
		if (*(str + 1) == '|')
			return (2);
	}
	else
	{
		if ((*str == '<' || *str == '>')
			&& (*(str + 1) != '<' && *(str + 1) != '>'))
			return (1);
		if ((*str == '<' || *str == '>')
			&& (*(str + 1) != '\0' && (*(str + 1) == '<' || *(str + 1) == '>')))
			return (2);
	}
	return (0);
}

/* s_quotes = 0  |  d_quotes = 1 */
static size_t	word_len(char *input)
{
	size_t	len;

	len = 0;
	while (*input)
	{
		if (!in_quotes(*input) && (is_whitespace(*input)
				|| *input == '<' || *input == '>' || *input == '|'))
		{
			len += operator_size(input);
			break ;
		}
		len++;
		if (!ms()->quote[0] && !ms()->quote[1] && (*(input + 1) == '<'
				|| *(input + 1) == '>' || *(input + 1) == '|'))
			break ;
		input++;
	}
	return (len);
}

t_type	get_type(char *word)
{
	if (!ft_strncmp("|", word, 2) || !ft_strncmp("||", word, 3))
		return (PIPE);
	if (!ft_strncmp("<", word, 2))
		return (REDIR_IN);
	if (!ft_strncmp(">", word, 2))
		return (REDIR_OUT);
	if (!strncmp("<<", word, 3))
		return (HEREDOC);
	if (!strncmp(">>", word, 3))
		return (REDIR2_OUT);
	else
		return (OTHER);
}

static void	add_lexer_node(char *word)
{
	t_token	*new;
	t_token	*tmp;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return ;
	new->content = word;
	new->type = get_type(word);
	new->next = NULL;
	new->prev = NULL;
	if (!ms()->lexer)
		ms()->lexer = new;
	else
	{
		tmp = ms()->lexer;
		while (tmp->next)
			tmp = tmp->next;
		new->prev = tmp;
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
		if (!*input)
			break ;
		len = word_len(input);
		word = ft_substr(input, 0, len);
		add_lexer_node(word);
		input += len;
		if (*input && !is_operator(word)
			&& *input != '<' && *input != '>' && *input != '|')
			input++;
	}
}
