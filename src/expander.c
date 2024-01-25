/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:23:55 by digoncal          #+#    #+#             */
/*   Updated: 2024/01/22 16:15:10 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_code;

static bool	check_heredoc(char *str, size_t i)
{
	char	*heredoc_pos;

	heredoc_pos = ft_strnstr(str, "<<", ft_strlen(str));
	if (i > 0 && str[i - 1] == '\"' && heredoc_pos
		&& heredoc_pos < str + i - 1)
		return (false);
	else if (i > 0 && str[i - 1] == '\"')
		return (true);
	else if (heredoc_pos && heredoc_pos < str + i)
		return (false);
	else
		return (true);
}

static void	expand(t_token *lexer)
{
	int	i;

	ms()->quote[0] = false;
	ms()->quote[1] = false;
	i = -1;
	while (lexer->content[++i])
	{
		in_quotes(lexer->content[i]);
		if (lexer->content[i] == '$' && !ms()->quote[0]
			&& (!lexer->prev || lexer->prev->type != HEREDOC))
		{
			if (check_heredoc(lexer->content, i))
			{
				if (expand_str(lexer, i))
					continue ;
				i = -1;
			}
		}
	}
}

int	expander(void)
{
	t_token		*tmp;

	tmp = ms()->lexer;
	while (tmp)
	{
		if (!valid_quotes(tmp->content))
			return (1);
		expand(tmp);
		tmp = tmp->next;
	}
	return (0);
}
