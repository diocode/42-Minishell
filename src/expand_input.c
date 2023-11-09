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

static char	*get_word(const char *str)
{
	char	*val;
	int		i;
	int		j;
	int		start;

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

static char	*create_str(t_prompt *prompt, char *str, char *var, char *word)
{
	size_t	final_length;
	char	*final_str;

	final_length = (ft_strlen(str) - ft_strlen(word)) + ft_strlen(var);
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
	return (final_str);
}

static char	*replace(t_prompt *prompt, char *str)
{
	char	*var;
	char	*word;
	char	*final_str;

	word = get_word(str);
	if (!ft_strncmp(word, "?", 1))
		prompt->exit_codes[prompt->flg[2]++] = 1;
	var = get_env(prompt, get_word(str));
	if (!var)
	{
		free(word);
		return (NULL);
	}
	final_str = create_str(prompt, str, var, word);
	free(word);
	free(var);
	return (final_str);
}

static void	expand_word(t_prompt *prompt, char **word)
{
	char	*tmp;
	int		j;

	j = -1;
	while ((*word)[++j])
	{
		if ((*word)[j] == '$' && is_expandable(*word))
		{
			tmp = replace(prompt, *word);
			if (tmp)
			{
				free(*word);
				*word = ft_strdup(tmp);
				free(tmp);
			}
		}
	}
	if (!is_expandable(*word) && is_exit_status(*word))
		prompt->exit_codes[prompt->flg[2]++] = 0;
}

char	*expand_input(t_prompt *prompt, char *input)
{
	char	**arr;
	int		i;

	prompt->flg[2] = 0;
	init_exit_codes(prompt, input);
	if (!prompt->exit_codes)
		return (NULL);
	arr = ft_split(input, ' ');
	if (!arr)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		expand_word(prompt, &arr[i]);
		i++;
	}
	return (array_to_str(arr));
}
