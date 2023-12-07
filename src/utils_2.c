/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:54:39 by digoncal          #+#    #+#             */
/*   Updated: 2023/11/09 14:54:39 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*Identifies a single $?*/
bool	is_exit_status(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
			if (str[i + 1] && str[i + 1] == '?')
				return (true);
	}
	return (false);
}

int	current_exit_status(t_prompt *prompt)
{
	int	i;

	i = 0;
	while (prompt->exit_codes[i] == 2)
		i++;
	return (i);
}

int	check_param(char *str)
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

bool	existing_var(char *env, char *str)
{
	int	size;

	size = 0;
	while (str[size] && str[size] != '=')
		size++;
	if (!ft_strncmp(env, str, size))
		return (true);
	return (false);
}
