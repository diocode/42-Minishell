/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:21:20 by digoncal          #+#    #+#             */
/*   Updated: 2023/06/23 12:24:54 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

void	ms_error(int err, int status, char *param)
{
	g_status = status;
	if (FORKERR == err)
		ft_putstr_fd("minishell: fork failed\n", 2);
	ft_putendl_fd(param, 2);
}

int	count_quotes(char const *str, int i)
{
	int	quotes;
	int	start;

	quotes = 0;
	start = i - 1;
	while (str[++start])
	{
		if (str[start] == '"')
		{
			quotes++;
			if (str[start + 1] == ' ' || (str[start + 1] >= 9
					&& str[start + 1] <= 13))
				if (quotes == 2
					|| ((str[start + 1] == ' ' || (str[start + 1] >= 9 && str[start + 1] <= 13))
					&& (str[start - 1] != ' ' && (str[start - 1] < 9 || str[start - 1] > 13))))
					return (quotes);
		}
		if (!quotes && str[start] == ' ')
			break ;
	}
	return (quotes);
}

int	total_quotes(char const *str)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (str[i])
	{
		if (str[i++] == '"')
			quotes++;
	}
	return (quotes);
}

char	**dup_arr(char **arr)
{
	char	**dup;
	int		i;

	i = 0;
	while (arr[i])
		i++;
	dup = ft_calloc(sizeof(char *), i + 1);
	if (!dup)
		return (NULL);
	i = -1;
	while (arr[++i])
	{
		dup[i] = ft_strdup(arr[i]);
		if (!dup[i])
		{
			free_array(dup);
			return (NULL);
		}
	}
	return (dup);
}

char	**extend_arr(char **arr, char *new)
{
	char	**new_arr;
	int		len;
	int		i;

	if (!new)
		return (arr);
	len = 0;
	while (arr[len])
		len++;
	new_arr = ft_calloc(sizeof(char *), len + 2);
	if (!new_arr)
		return (arr);
	i = -1;
	while (len > ++i)
	{
		new_arr[i] = ft_strdup(arr[i]);
		if (!new_arr[i])
		{
			free_array(arr);
			free_array(new_arr);
		}
	}
	new_arr[i] = ft_strdup(new);
	return (new_arr);
}
