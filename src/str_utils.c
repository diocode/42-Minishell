/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:21:20 by digoncal          #+#    #+#             */
/*   Updated: 2023/10/24 16:27:25 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**dup_arr(char **arr)
{
	char	**dup;
	int		i;

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

static void	cat_str(char **str, char *result, size_t total_length)
{
	while (*str != NULL)
	{
		ft_strlcat(result, *str, total_length + 1);
		if (*(str + 1) != NULL)
			ft_strlcat(result, " ", total_length + 1);
		str++;
	}
}

char	*array_to_str(char **arr)
{
	char	**str;
	char	*result;
	size_t	total_length;

	total_length = 0;
	str = arr;
	if (arr == NULL || arr[0] == NULL)
		return (NULL);
	while (*str != NULL)
	{
		total_length += strlen(*str);
		str++;
	}
	total_length += (size_t)(str - arr - 1);
	result = malloc(total_length + 1);
	if (result == NULL)
		return (NULL);
	result[0] = '\0';
	str = arr;
	cat_str(str, result, total_length);
	free_array(arr);
	return (result);
}
