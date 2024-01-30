/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 01:53:23 by digoncal          #+#    #+#             */
/*   Updated: 2024/01/30 01:53:23 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	array_len(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
		i++;
	return (i);
}

static char	*get_value(char	**array, int i, char *value)
{
	array[i] = ft_strjoin(array[i], value);
	if (!array[i])
	{
		free_array(array);
		return (NULL);
	}
	return (array[i]);
}

static int	list_size(t_env *list)
{
	int	i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

char	**list_to_array(t_env *list)
{
	char	**array;
	int		i;

	array = ft_calloc(list_size(list) + 1, sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	while (list)
	{
		array[i] = ft_strjoin(list->key, "=");
		if (!array[i])
		{
			free_array(array);
			return (NULL);
		}
		if (list->value)
		{
			array[i] = get_value(array, i, list->value);
			if (!array[i])
				return (NULL);
		}
		list = list->next;
		i++;
	}
	return (array);
}

char	**dup_arr(char **arr)
{
	char	**dup;
	int		i;

	if (!arr)
		return (NULL);
	i = 0;
	while (arr[i])
		i++;
	dup = ft_calloc(i + 1, sizeof(char *));
	if (!dup)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		dup[i] = ft_strdup(arr[i]);
		if (!dup[i])
		{
			free_array(dup);
			return (NULL);
		}
		i++;
	}
	return (dup);
}
