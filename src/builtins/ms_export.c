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

/*NOT MY CODE: USE THIS JUST FOR TESTING*/

static int	variable_exist(t_prompt *prompt, char *str)
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

static int	check_parameter(char *str)
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
		if (check_valid_identifier(str[i]))
			return (export_error(str));
		i++;
	}
	return (EXIT_SUCCESS);
}

static char	**whileloop_add_var(char **arr, char **rtn, char *str)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		if (arr[i + 1] == NULL)
		{
			rtn[i] = ft_strdup(str);
			rtn[i + 1] = ft_strdup(arr[i]);
		}
		else
			rtn[i] = ft_strdup(arr[i]);
		if (rtn[i] == NULL)
		{
			free_array(rtn);
			return (rtn);
		}
		i++;
	}
	return (rtn);
}

static char	**add_var(char **arr, char *str)
{
	char	**rtn;
	size_t	i;

	i = 0;
	if (str[equal_sign(str)] == '\"')
		delquotes(str, '\"');
	if (str[equal_sign(str)] == '\'')
		delquotes(str, '\'');
	while (arr[i] != NULL)
		i++;
	rtn = ft_calloc(sizeof(char *), i + 2);
	if (!rtn)
		return (NULL);
	rtn = whileloop_add_var(arr, rtn, str);
	return (rtn);
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
			if (check_parameter(simple_cmds->str[i]) == 0
				&& variable_exist(prompt, simple_cmds->str[i]) == 0)
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
