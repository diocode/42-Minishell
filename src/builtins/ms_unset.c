/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:24:03 by digoncal          #+#    #+#             */
/*   Updated: 2023/10/19 13:26:51 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

static char	**var_del_2(char **arr, char **res, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arr[i] != NULL)
	{
		if (!(ft_strncmp(arr[i], str, equal_sign(arr[i]) - 2) == 0
				&& str[equal_sign(arr[i])] == '\0'
				&& arr[i][ft_strlen(str)] == '='))
		{
			res[j] = ft_strdup(arr[i]);
			if (res[j] == NULL)
			{
				free_array(res);
				return (res);
			}
			j++;
		}
		i++;
	}
	return (res);
}

static char	**var_del(char **arr, char *str)
{
	char	**res;
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	res = ft_calloc(i + 1, sizeof(char *));
	if (!res)
		return (NULL);
	res = var_del_2(arr, res, str);
	return (res);
}

static int	error(t_simple_cmds *simple_cmds)
{
	int		i;

	i = 0;
	if (!simple_cmds->str[1])
	{
		ft_putendl_fd("unset: not enough arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	while (simple_cmds->str[1][i])
	{
		if (is_digit(simple_cmds->str[1])
			|| (!ft_isalnum(simple_cmds->str[1][i])
			&& simple_cmds->str[1][i] != '_'))
		{
			ft_putstr_fd("unset: `", STDERR_FILENO);
			ft_putstr_fd(simple_cmds->str[1], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ms_unset(t_prompt *prompt, t_simple_cmds *simple_cmds)
{
	char	**tmp;

	if (error(simple_cmds) == 1)
		return (EXIT_FAILURE);
	else
	{
		tmp = var_del(prompt->env, simple_cmds->str[1]);
		free_array(prompt->env);
		prompt->env = tmp;
	}
	return (EXIT_SUCCESS);
}
