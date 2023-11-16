/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:23:44 by digoncal          #+#    #+#             */
/*   Updated: 2023/10/17 18:08:53 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_variable(t_prompt *prompt, char *str)
{
	int	i;

	if (str[equal_sign(str)] == '\"')
		delquotes(str, '\"');
	if (str[equal_sign(str)] == '\'')
		delquotes(str, '\'');
	i = -1;
	while (prompt->env[++i])
	{
		if (existing_var(prompt->env[i], str))
		{
			if (!equal_sign(str))
				return (1);
			free(prompt->env[i]);
			prompt->env[i] = ft_strdup(str);
			return (1);
		}
	}
	return (0);
}

static char	**copy_arr(char **arr, char **res, char *str)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		if (arr[i + 1] == NULL)
		{
			res[i] = ft_strdup(str);
			res[i + 1] = ft_strdup(arr[i]);
		}
		else
			res[i] = ft_strdup(arr[i]);
		if (res[i] == NULL)
		{
			free_array(res);
			return (res);
		}
		i++;
	}
	return (res);
}

static char	**add_var(char **arr, char *str)
{
	char	**res;
	size_t	i;

	i = 0;
	if (str[equal_sign(str)] == '\"')
		delquotes(str, '\"');
	if (str[equal_sign(str)] == '\'')
		delquotes(str, '\'');
	while (arr[i] != NULL)
		i++;
	res = ft_calloc(i + 2, sizeof(char *));
	if (!res)
		return (NULL);
	res = copy_arr(arr, res, str);
	return (res);
}

int	ms_export(t_prompt *prompt, t_simple_cmds *simple_cmds)
{
	char	**tmp;
	int		i;

	i = 1;
	if (!simple_cmds->str[1] || simple_cmds->str[1][0] == '\0')
		ms_env(prompt, 1);
	else
	{
		while (simple_cmds->str[i])
		{
			if (check_param(simple_cmds->str[i]) == 0
				&& is_variable(prompt, simple_cmds->str[i]) == 0)
			{
				if (simple_cmds->str[i])
				{
					tmp = add_var(prompt->env, simple_cmds->str[i]);
					free_array(prompt->env);
					prompt->env = tmp;
				}
			}
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
