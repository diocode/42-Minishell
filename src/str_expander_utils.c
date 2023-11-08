/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_expander_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 12:47:59 by digoncal          #+#    #+#             */
/*   Updated: 2023/11/08 14:46:57 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

int	if_question_mark(void)
{
	char	*tmp;

	tmp = ft_itoa(g_status);
	ft_putstr_fd(tmp, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	free(tmp);
	return (127);
}

int	if_digit(char *str, int i)
{
	if (str[i] == '$')
		if (ft_isdigit(str[i + 1]))
			return (2);
	return (0);
}

char	*char_to_str(char c)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	str[0] = c;
	return (str);
}

int	equal_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i + 1);
		i++;
	}
	return (0);
}

int	dol_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i + 1);
		i++;
	}
	return (0);
}
