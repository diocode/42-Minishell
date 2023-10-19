/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:24:03 by digoncal          #+#    #+#             */
/*   Updated: 2023/10/16 16:24:03 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

/*NOT MY CODE: USE THIS JUST FOR TESTING*/

static char	**whileloop_del_var(char **arr, char **rtn, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arr[i] != NULL)
	{
		if (!(ft_strncmp(arr[i], str, equal_sign(arr[i]) - 1) == 0
				&& str[equal_sign(arr[i])] == '\0'
				&& arr[i][ft_strlen(str)] == '='))
		{
			rtn[j] = ft_strdup(arr[i]);
			if (rtn[j] == NULL)
			{
				free_array(rtn);
				return (rtn);
			}
			j++;
		}
		i++;
	}
	return (rtn);
}

static char	**del_var(char **arr, char *str)
{
	char	**rtn;
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	rtn = ft_calloc(sizeof(char *), i + 1);
	if (!rtn)
		return (NULL);
	rtn = whileloop_del_var(arr, rtn, str);
	return (rtn);
}

static int	unset_error(t_simple_cmds *simple_cmds)
{
	int		i;

	i = 0;
	if (!simple_cmds->str[1])
	{
		ft_putendl_fd("minishell: unset: not enough arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	while (simple_cmds->str[1][i])
	{
		if (simple_cmds->str[1][i++] == '/')
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(simple_cmds->str[1], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
	}
	if (equal_sign(simple_cmds->str[1]) != 0)
	{
		ft_putendl_fd("minishell: unset: not a valid identifier",
			STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ms_unset(t_prompt *prompt, t_simple_cmds *simple_cmds)
{
	char	**tmp;

	if (unset_error(simple_cmds) == 1)
		return (EXIT_FAILURE);
	else
	{
		tmp = del_var(prompt->env, simple_cmds->str[1]);
		free_array(prompt->env);
		prompt->env = tmp;
	}
	return (EXIT_SUCCESS);
}
