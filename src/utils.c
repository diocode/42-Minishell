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

char	*delquotes(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			j = 0;
			while (str[i + j] == c)
				j++;
			ft_strlcpy(&str[i], &str[i + j], strlen(str) - i);
		}
		i++;
	}
	return (str);
}

int	is_whitespace(char c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

int	error_cmd_not_found(t_prompt *prompt)
{
	char	*str;
	char	*tmp;

	if (!prompt->lexer->str && !prompt->lexer->str[0])
		return (1);
	tmp = ft_strdup(prompt->lexer->str);
	str = ft_strjoin("zsh: command not found: ", tmp);
	ft_putendl_fd(str, STDERR_FILENO);
	free(tmp);
	free(str);
	return (1);
}

int	ms_error(int error)
{
	g_status = error;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (error == 0)
		ft_putstr_fd("syntax error near unexpected token 'newline'\n",
			STDERR_FILENO);
	else if (error == 1)
		ft_putstr_fd("memory error: unable to assign memory\n", STDERR_FILENO);
	else if (error == 2)
		ft_putstr_fd("syntax error: unable to locate closing quotation\n",
			STDERR_FILENO);
	else if (error == 3)
		ft_putstr_fd("Parser problem\n", STDERR_FILENO);
	else if (error == 4)
		ft_putstr_fd("Failed to create pipe\n", STDERR_FILENO);
	else if (error == 5)
		ft_putstr_fd("Failed to fork\n", STDERR_FILENO);
	else if (error == 6)
		ft_putstr_fd("outfile: Error\n", STDERR_FILENO);
	else if (error == 7)
		ft_putstr_fd("infile: No such file or directory\n", STDERR_FILENO);
	else if (error == 8)
		ft_putendl_fd("Path does not exist", STDERR_FILENO);
	return (1);
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
