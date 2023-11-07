/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:25:32 by digoncal          #+#    #+#             */
/*   Updated: 2023/11/06 16:25:32 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                    +:+ +:+         +:+     */
/*                                                        :::      ::::::::   */
/*   replace_variables.c                                :+:      :+:    :+:   */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:16:19 by digoncal          #+#    #+#             */
/*   Updated: 2023/11/04 16:57:48 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_double_qts(t_prompt *prompt, char *str)
{
	int		i;
	int		j;

	i = -1;
	while (prompt->input[++i])
	{
		if (prompt->input[i] == '$')
		{
			j = 0;
			while (prompt->input[i] && str[j] && prompt->input[i] == str[j])
			{
				i++;
				j++;
			}
			if (prompt->input[i] == '\"')
				return (1);
			else
				return (0);
		}
	}
	return (0);
}

char    *get_env(t_prompt *prompt, char *val)
{
	int       i[3];

	if (!val)
		return (NULL);
	i[0] = -1;
	while (prompt->env[++i[0]])
	{
		if (!ft_strncmp(val, prompt->env[i[0]], ft_strlen(val)))
		{
			free(val);
			i[1] = 0;
			while (prompt->env[i[0]][i[1]] != '=')
				i[1]++;
			val = ft_calloc(ft_strlen(prompt->env[i[0]]) - i[1] + 1,
							sizeof(char));
			if (!val)
				return (NULL);
			i[2] = -1;
			while (prompt->env[i[0]][i[1]])
				val[++i[2]] = prompt->env[i[0]][++i[1]];
			return (val);
		}
	}
	free(val);
	return (NULL);
}

static char    *get_word(char *str)
{
	char   *val;
	int       i;
	int       j;
	int       start;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	i++;
	start = i;
	while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '\"')
		i++;
	val = ft_calloc(i - start + 1, sizeof(char));
	j = 0;
	while (start < i)
		val[j++] = str[start++];
	return (val);
}

bool    is_expandable(char *str)
{
	bool   in_double_quotes;
	bool   in_single_quotes;
	int       i;

	in_double_quotes = false;
	in_single_quotes = false;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\')
			&& !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (str[i] == '"' && (i == 0 || str[i - 1] != '\\')
				 && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else if (str[i] == '$' && in_single_quotes)
			return (false);
		i++;
	}
	return (true);
}

static char    *replace(t_prompt *prompt, char *str)
{
	char   *final_str;
	char   *var;
	char	*word;
	size_t	final_length

	word = get_word(str);
	var = get_env(prompt, get_word(str));
	if (!var)
	{
		free(word);
		return (NULL);
	}
	size_t final_length = (ft_strlen(str) - ft_strlen(word)) + ft_strlen(var);
	final_str = ft_calloc(final_length + 1, sizeof(char));
	if (!final_str)
		return (NULL);
	prompt->flg[0] = 0;
	prompt->flg[1] = 0;

	while (str[prompt->flg[0]] != '$')
		final_str[prompt->flg[1]++] = str[prompt->flg[0]++];
	ft_strlcat(final_str, var, final_length + 1);
	prompt->flg[0] += ft_strlen(word) + 1;
	while (final_str[prompt->flg[1]])
		prompt->flg[1]++;
	while (str[prompt->flg[0]])
		final_str[prompt->flg[1]++] = str[prompt->flg[0]++];
	free(word);
	free(var);
	return (final_str);
}

char *array_to_str(char **arr)
{
	char *result;
	size_t total_length;
	char **str;

	total_length = 0;
	str = arr;
	if (arr == NULL || arr[0] == NULL)
		return NULL;
	while (*str != NULL)
	{
		total_length += strlen(*str);
		str++;
	}
	total_length += (size_t)(str - arr - 1);
	result = malloc(total_length + 1);
	if (result == NULL)
		return NULL;
	result[0] = '\0';
	str = arr;
	while (*str != NULL)
	{
		ft_strlcat(result, *str, total_length + 1);
		if (*(str + 1) != NULL)
			ft_strlcat(result, " ", total_length + 1);
		str++;
	}
	free_array(arr);
	return (result);
}


char   *expand_input(t_prompt *prompt, char *input)
{
	char   **arr;
	char   *tmp;
	int       i;
	int       j;

	arr = ft_split(input, ' ');
	if (!arr)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		j = -1;
		while (arr[i][++j])
		{
			if (arr[i][j] == '$')
				if (is_expandable(arr[i]))
				{
					tmp = replace(prompt, arr[i]);
					if (tmp)
					{
						free(arr[i]);
						arr[i] = ft_strdup(tmp);
						free(tmp);
					}

				}
		}
		i++;
	}
	return (array_to_str(arr));
}