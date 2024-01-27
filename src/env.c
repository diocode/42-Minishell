/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:09:06 by digoncal          #+#    #+#             */
/*   Updated: 2024/01/18 13:09:06 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_env	*create_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (ms_error(1), NULL);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}

t_env	*copy_env(t_env *env)
{
	t_env 	*sorted;
	t_env	*new_node;
	t_env	*last_node;

	sorted = NULL;
	while (env)
	{
		new_node = create_node(env->key, env->value);
		if (!new_node)
			return (NULL);
		if (!sorted)
			sorted = new_node;
		else
		{
			last_node = sorted;
			while (last_node->next)
				last_node = last_node->next;
			last_node->next = new_node;
		}
		env = env->next;
	}
	return (sorted);
}

char	*ms_getenv(char *key)
{
	t_env	*tmp;

	if (!key)
		return (NULL);
	tmp = ms()->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

void	ms_setenv(char *key, char *value)
{
	t_env	*tmp;

	if (!key || !value)
		return ;
	tmp = ms()->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	tmp = malloc(sizeof(t_env));
	if (!tmp)
		return ;
	tmp->key = ft_strdup(key);
	tmp->value = ft_strdup(value);
	tmp->next = ms()->env;
	ms()->env = tmp;
}
