/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:35:46 by digoncal          #+#    #+#             */
/*   Updated: 2023/11/08 11:35:46 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*delquotes(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			j = 0;
			while (str[i + j] == c)
				j++;
			ft_strlcpy(&str[i], &str[i + j], strlen(str) - i);
		}
		i++;
	}
	return (str);
}

int	is_whitespace(char c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

int	is_identifier(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '[' || c == ']'
		|| c == '\'' || c == '\"' || c == ' ' || c == ',' || c == '.'
		|| c == ':' || c == '/' || c == '{' || c == '}' || c == '+'
		|| c == '^' || c == '%' || c == '#' || c == '@' || c == '!'
		|| c == '~'
		|| c == '=' || c == '-' || c == '?' || c == '&' || c == '*');
}

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	init_exit_codes(t_prompt *prompt, char *input)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (input[++i])
	{
		if (input[i] == '$')
			if (input[i + 1] && input[i + 1] == '?')
				count++;
	}
	if (!count)
		return ;
	prompt->exit_codes = malloc(count * sizeof(int));
	if (!prompt->exit_codes)
		return ;
	i = -1;
	while (++i < count)
		prompt->exit_codes[i] = 0;
}
