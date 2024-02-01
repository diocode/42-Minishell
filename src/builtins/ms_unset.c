/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:37:00 by digoncal          #+#    #+#             */
/*   Updated: 2024/01/27 20:37:00 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	del_variable(t_env *env, t_env *prev)
{
	prev->next = env->next;
	if (env->key)
		free(env->key);
	if (env->value)
		free(env->value);
	free(env);
}

static int	error(t_process *process)
{
	int		i;

	i = 0;
	if (!process->args)
		return (EXIT_FAILURE);
	if (!process->args[0])
	{
		ft_putstr_fd("minishell: unset: `': not a valid identifier\n", 2);
		return (2);
	}
	while (process->args[0][i])
	{
		if (is_digit(process->args[0])
			|| (!ft_isalnum(process->args[0][i])
			&& process->args[0][i] != '_'))
		{
			ft_putstr_fd("unset: `", STDERR_FILENO);
			ft_putstr_fd(process->args[0], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ms_unset(t_process *process)
{
	t_env	*tmp;
	t_env	*tmp_prev;
	int		i;

	if (error(process) == 2)
		return (1);
	else if (error(process) == EXIT_SUCCESS)
	{
		i = -1;
		while (process->args[++i])
		{
			tmp = ms()->env;
			while (tmp)
			{
				if (existing_key(tmp, process->args[i]))
				{
					del_variable(tmp, tmp_prev);
					break ;
				}
				tmp_prev = tmp;
				tmp = tmp->next;
			}
		}
	}
	return (EXIT_SUCCESS);
}
