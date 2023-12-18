/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:44:34 by digoncal          #+#    #+#             */
/*   Updated: 2023/12/18 19:03:23 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env(t_prompt *p, char *val)
{
	int	i[3];

	if (!val)
		return (NULL);
	i[0] = -1;
	while (p->env[++i[0]])
	{
		if (!ft_strncmp(val, p->env[i[0]], equal_sign(p->env[i[0]]) - 1))
		{
			free(val);
			i[1] = 0;
			while (p->env[i[0]][i[1]] != '=')
				i[1]++;
			val = ft_calloc(ft_strlen(p->env[i[0]]) - i[1] + 1,
					sizeof(char));
			if (!val)
				return (NULL);
			i[2] = -1;
			while (p->env[i[0]][i[1]])
				val[++i[2]] = p->env[i[0]][++i[1]];
			return (val);
		}
	}
	free(val);
	return (NULL);
}

bool	solo_doll_sign(const char *str)
{
	int	i;
	int	doll;

	doll = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
			doll++;
		if (str[i] != '\'' && str[i] != '\"' && str[i] != '$')
			return (false);
	}
	if (doll > 1)
		return (false);
	return (true);
}

bool	is_expandable(const char *str)
{
	bool	in_double_quotes;
	bool	in_single_quotes;
	int		i;

	in_double_quotes = false;
	in_single_quotes = false;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\')
			&& !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (str[i] == '"' && (i == 0 || str[i - 1] != '\\')
			&& !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else if (str[i] == '$' && in_single_quotes)
			return (false);
		i++;
	}
	return (true);
}
