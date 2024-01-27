/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 22:34:03 by digoncal          #+#    #+#             */
/*   Updated: 2024/01/26 22:34:03 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_code;

bool	existing_key(t_env	*env, char *str)
{
	int	size;

	size = 0;
	while (str && str[size] && str[size] != '=')
		size++;
	if (ft_strlen(env->key) != size)
		return (false);
	if (!ft_strncmp(env->key, str, size))
		return (true);
	return (false);
}

static int	is_variable(char *str)
{
	t_env	*tmp;

	if (str[equal_sign(str) + 1] == '\"')
		clean_quotes(str, '\"');
	if (str[equal_sign(str) + 1] == '\'')
		clean_quotes(str, '\'');
	tmp = ms()->env;
	while (tmp)
	{
		if (existing_key(tmp, str))
		{
			if (!equal_sign(str))
				return (1);
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(str + equal_sign(str) + 1);
			if (!tmp->value)
				return (g_exit_code = 1, 1);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static void	add_var(char *str)
{
	t_env	*tmp;

	if (str[equal_sign(str)] == '\"')
		clean_quotes(str, '\"');
	if (str[equal_sign(str)] == '\'')
		clean_quotes(str, '\'');
	tmp = ms()->env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = create_node(NULL, NULL);
	free(tmp->next->key);
	free(tmp->next->value);
	if (equal_sign(str))
	{
		tmp->next->key = ft_substr(str, 0, equal_sign(str));
		tmp->next->value = ft_strdup(str + equal_sign(str) + 1);
		return ;
	}
	tmp->next->key = ft_strdup(str);
	tmp->next->value = NULL;
}

int	check_arg(char *str)
{
	int	i;

	i = 0;
	if (!str[0] || ft_isdigit(str[0]) || str[0] == '=')
		return (export_error(str));
	if (!ft_strncmp(str, "_", 2))
		return (EXIT_FAILURE);
	while (str[i] && str[i] != '=')
	{
		if (is_identifier(str[i]))
			return (export_error(str));
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ms_export(t_process *process)
{
	int		i;

	if (!process->args || !process->args[0])
	{
		if (ms_env(true))
			return (EXIT_FAILURE);
	}
	else
	{
		i = -1;
		while (process->args[++i])
		{
			if (!check_arg(process->args[i]))
			{
				if (!is_variable(process->args[i])
					&& process->args[i])
					add_var(process->args[i]);
			}
			else
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
