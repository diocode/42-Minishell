/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:44:34 by digoncal          #+#    #+#             */
/*   Updated: 2023/12/20 13:44:07 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*extract_env_value(char *env_entry)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	while (env_entry[i] && env_entry[i] != '=')
		i++;
	value = ft_calloc(ft_strlen(env_entry) - i, sizeof(char));
	if (!value)
		return (NULL);
	j = 0;
	i = 0;
	while (env_entry[i] && env_entry[i] != '=')
		i++;
	i++;
	while (env_entry[i])
		value[j++] = env_entry[i++];
	return (value);
}

char	*get_env(t_prompt *p, char *val)
{
	char	*var;
	char	*value;
	int		i;
	int		len;

	if (!val)
		return (NULL);
	i = -1;
	while (p->env[++i])
	{
		var = ft_substr(p->env[i], 0, equal_sign(p->env[i]) - 1);
		len = ft_strlen(val);
		if (len < ft_strlen(var))
			len = ft_strlen(var);
		if (!ft_strncmp(val, var, len))
		{
			free(val);
			value = extract_env_value(p->env[i]);
			free(var);
			return (value);
		}
		free(var);
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
