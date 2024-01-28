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

int	is_whitespace(char c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

int	is_identifier(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '[' || c == ']'
			|| c == '\'' || c == '\"' || c == ' ' || c == ',' || c == '.'
			|| c == ':' || c == '/' || c == '{' || c == '}' || c == '+'
			|| c == '^' || c == '%' || c == '#' || c == '@' || c == '!'
			|| c == '~'
			|| c == '=' || c == '-' || c == '?' || c == '&' || c == '*');
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

bool	is_builtin(char *str)
{
	if (!str)
		return (false);
	if (!ft_strncmp(str, "echo", 5) || !ft_strncmp(str, "cd", 3)
		|| !ft_strncmp(str, "pwd", 4) || !ft_strncmp(str, "export", 7)
		|| !ft_strncmp(str, "unset", 6) || !ft_strncmp(str, "env", 4)
		|| !ft_strncmp(str, "exit", 5))
		return (true);
	return (false);
}

int	equal_sign(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

char	*clean_quotes(char *str, char c)
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

static char *get_value(char	**array, int i, char *value)
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