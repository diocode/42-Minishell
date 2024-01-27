/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 22:40:25 by digoncal          #+#    #+#             */
/*   Updated: 2024/01/26 22:40:25 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	swap_env_nodes(t_env *node1, t_env *node2)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = node1->key;
	tmp_value = node1->value;
	node1->key = node2->key;
	node1->value = node2->value;
	node2->key = tmp_key;
	node2->value = tmp_value;
}

static t_env	*sort_env(t_env *env)
{
	t_env	*sorted;
	t_env	*tmp;
	t_env	*tmp_next;

	sorted = copy_env(env);
	if (!sorted)
		return (NULL);
	tmp = sorted;
	while (tmp != NULL)
	{
		tmp_next = tmp->next;
		while (tmp_next)
		{
			if (ft_strcmp(tmp->key, tmp_next->key) > 0)
				swap_env_nodes(tmp, tmp_next);
			tmp_next = tmp_next->next;
		}
		tmp = tmp->next;
	}
	return (sorted);
}

static void	print_env(t_env *env, bool export)
{
	while (env && export)
	{
		write(STDOUT_FILENO, "declare -x ", 11);
		write(STDOUT_FILENO, env->key, ft_strlen(env->key));
		if (env->value)
		{
			write(STDOUT_FILENO, "=", 1);
			write(STDOUT_FILENO, "\"", 1);
			write(STDOUT_FILENO, env->value, ft_strlen(env->value));
			write(STDOUT_FILENO, "\"", 1);
		}
		write(STDOUT_FILENO, "\n", 1);
		env = env->next;
	}
	while (env && !export)
	{
		if (env->value)
		{
			write(STDOUT_FILENO, env->key, ft_strlen(env->key));
			write(STDOUT_FILENO, "=", 1);
			write(STDOUT_FILENO, env->value, ft_strlen(env->value));
			write(STDOUT_FILENO, "\n", 1);
		}
		env = env->next;
	}
}

int	ms_env(bool export)
{
	t_env	*env;
	t_env	*sorted;

	sorted = NULL;
	env = ms()->env;
	if (export)
	{
		sorted = sort_env(env);
		if (!sorted)
			return (1);
		print_env(sorted, export);
		free_env(sorted);
	}
	else
		print_env(env, export);
	return (0);
}
