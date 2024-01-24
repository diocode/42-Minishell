/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:04:12 by digoncal          #+#    #+#             */
/*   Updated: 2024/01/18 17:04:12 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_code;

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

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

int	is_whitespace(char c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

void	skip_spaces(char **line)
{
	while (**line && is_whitespace(**line))
		(*line)++;
}

bool	in_quotes(char c)
{
	if (c == '\'' && !ms()->quote[1])
		ms()->quote[0] = !ms()->quote[0];
	else if (c == '\"' && !ms()->quote[0])
		ms()->quote[1] = !ms()->quote[1];
	return (ms()->quote[0] || ms()->quote[1]);
}

bool	valid_quotes(char *str)
{
	int	i;

	ms()->quote[0] = false;
	ms()->quote[1] = false;
	i = 0;
	while (str[i])
		in_quotes(str[i++]);
	if (ms()->quote[0] || ms()->quote[1])
	{
		g_exit_code = 2;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("unexpected EOF while looking for matching `", 2);
		if (ms()->quote[0])
			ft_putchar_fd('\'', STDERR_FILENO);
		else
			ft_putchar_fd('\"', STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		return (false);
	}
	return (true);
}

int	count_pipes(t_token *lx)
{
	t_token	*tmp;
	int		pipes;

	tmp = lx;
	pipes = 0;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, "|", 2)
			|| !ft_strncmp(tmp->content, "||", 3))
			pipes++;
		tmp = tmp->next;
	}
	return (pipes);
}

bool	is_redirect(char *str)
{
	if (!str)
		return (0);
	if ((str[0] == '<' || str[0] == '>') && ft_strlen(str) == 1)
		return (true);
	if ((!ft_strncmp(str, "<<", 2) || !ft_strncmp(str, ">>", 2))
		&& ft_strlen(str) == 2)
		return (true);
	return (false);
}

bool	is_operator(char *str)
{
	if (!str)
		return (0);
	if ((str[0] == '<' || str[0] == '>' || str[0] == '|')
		&& ft_strlen(str) == 1)
		return (true);
	if ((!ft_strncmp(str, "<<", 2) || !ft_strncmp(str, ">>", 2)
			|| !ft_strncmp(str, "||", 2)) && ft_strlen(str) == 2)
		return (true);
	return (false);
}
