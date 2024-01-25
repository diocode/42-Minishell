/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 02:58:36 by digoncal          #+#    #+#             */
/*   Updated: 2024/01/25 02:58:36 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	del_quotes(char *str, char	*quote, size_t i, size_t len)
{
	bool	in_quotes;

	in_quotes = false;
	if (!*(quote + 1))
		in_quotes = true;
	ft_memmove(str + i, str + i + 1, quote - (str + i));
	ft_memmove(quote - 1, quote + 1, len - (quote - str));
	return (in_quotes);
}

static void	remove_quotes(char *str)
{
	char	*quote;
	size_t	len;
	size_t	i;

	len = ft_strlen(str);
	i = 0;
	while (i < len)
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = ft_strchr(str + i + 1, str[i]);
			if (quote)
			{
				if (del_quotes(str, quote, i, len))
					return ;
				len -= 2;
			}
			else
				i++;
		}
		else
			i++;
	}
}

void	trim_quotes(void)
{
	t_token	*tmp;
	char	*str;

	tmp = ms()->lexer;
	while (tmp)
	{
		str = tmp->content;
		remove_quotes(str);
		tmp = tmp->next;
	}
}
