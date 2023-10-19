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

extern int	g_status;

static int	is_variable(t_prompt *prompt, char *str)
{
	int	i;

	i = 0;
	if (str[equal_sign(str)] == '\"')
		delquotes(str, '\"');
	if (str[equal_sign(str)] == '\'')
		delquotes(str, '\'');
	while (prompt->env[i])
	{
		if (ft_strncmp(prompt->env[i], str, equal_sign(prompt->env[i])) == 0)
		{
			free(prompt->env[i]);
			prompt->env[i] = ft_strdup(str);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_param(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
		return (export_error(str));
	if (equal_sign(str) == 0)
		return (EXIT_FAILURE);
	if (str[0] == '=')
		return (export_error(str));
	while (str[i] != '=')
	{
		if (is_identifier(str[i]))
			return (export_error(str));
		i++;
	}
	return (EXIT_SUCCESS);
}

static char	**add_var_2(char **arr, char **res, char *str)
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
	res = ft_calloc(sizeof(char *), i + 2);
	if (!res)
		return (NULL);
	res = add_var_2(arr, res, str);
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
