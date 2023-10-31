/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:57:28 by digoncal          #+#    #+#             */
/*   Updated: 2023/10/17 17:59:26 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

static bool	is_in_array(char *str, char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		if (!ft_strncmp(str, arr[i], ft_strlen(str)))
			return (true);
	return (false);
}

static int	get_smaller(char **arr, char **sorted)
{
	int	smallest;
	int	i;

	smallest = -1;
	i = 0;
	while (arr[i])
	{
		if (!is_in_array(arr[i], sorted))
			if (smallest == -1 || strcmp(arr[i], arr[smallest]) < 0)
				smallest = i;
		i++;
	}
	return (smallest);
}

static char	**sort_env(t_prompt *prompt)
{
	char	**sorted;
	int		len;
	int		i;

	len = 0;
	while (prompt->env[len])
		len++;
	sorted = ft_calloc(len + 1, sizeof(char *));
	if (!sorted)
		return (NULL);
	i = 0;
	while (i < len)
		sorted[i++] = prompt->env[get_smaller(prompt->env, sorted)];
	return (sorted);
}

void	print_sorted(char **env)
{
	int		i;
	int		j;
	bool	flg;

	i = 0;
	while (env[i])
	{
		flg = false;
		write(STDOUT_FILENO, "declare -x ", 11);
		j = 0;
		while (env[i][j])
		{
			write(STDOUT_FILENO, &env[i][j], 1);
			if (env[i][j] == '=' && !flg)
			{
				write(STDOUT_FILENO, "\"", 1);
				flg = true;
			}
			j++;
		}
		if (flg)
			write(STDOUT_FILENO, "\"", 1);
		i++;
		write(STDOUT_FILENO, "\n", 1);
	}
}

void	ms_env(t_prompt *prompt, bool sort)
{
	char	**sorted;
	int		i;

	sorted = NULL;
	i = -1;
	if (sort)
	{
		sorted = sort_env(prompt);
		print_sorted(sorted);
		free(sorted);
	}
	else
	{
		while (prompt->env[++i])
			ft_putendl_fd(prompt->env[i], STDOUT_FILENO);
	}
}
