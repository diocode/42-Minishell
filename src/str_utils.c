/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 01:57:56 by digoncal          #+#    #+#             */
/*   Updated: 2024/01/30 01:57:56 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_code;

void	skip_spaces(char **line)
{
	while (**line && is_whitespace(**line))
		(*line)++;
}

int	equal_sign(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

bool	in_quotes(char c)
{
	if (c == '\'' && !ms()->quote[1])
		ms()->quote[0] = !ms()->quote[0];
	else if (c == '\"' && !ms()->quote[0])
		ms()->quote[1] = !ms()->quote[1];
	return (ms()->quote[0] || ms()->quote[1]);
}

bool	valid_quotes(char *str)
{
	int	i;

	ms()->quote[0] = false;
	ms()->quote[1] = false;
	i = 0;
	while (str[i])
		in_quotes(str[i++]);
	if (ms()->quote[0] || ms()->quote[1])
	{
		g_exit_code = 2;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("unexpected EOF while looking for matching `", 2);
		if (ms()->quote[0])
			ft_putchar_fd('\'', STDERR_FILENO);
		else
			ft_putchar_fd('\"', STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		return (false);
	}
	return (true);
}

char	*clean_quotes(char *str, char c)
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
