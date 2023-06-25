/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:03:44 by digoncal          #+#    #+#             */
/*   Updated: 2023/06/25 21:20:51 by logname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_whitespace(char c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

static int	count_words(char const *str)
{
	int	i;
	int	words;
	int	flg;

	i = 0;
	words = 0;
	while (str[i])
	{
		flg = 0;
		if (!is_whitespace(str[i]))
		{
			words++;
			if (str[i] == '"')
				flg = 1;
			while ((!is_whitespace(str[i]) || flg) && str[i])
			{
				if (str[++i] == '"')
					flg = 0;
			}
		}
		else
			i++;
	}
	return (words);
}

static int	word_size(char const *str, int i)
{
	int	len;
	int	flg;

	len = 0;
	flg = 0;
	if (str[i] == '"')
	{
		flg = 1;
		len++;
		i++;
	}
	while ((!is_whitespace(str[i]) || flg) && str[i])
	{
		if (str[i] == '"')
			flg = 0;
		len++;
		i++;
	}
	return (len);
}

static char	*get_word(char **arr, char *str, int i)
{
	char	*word;
	int		size;

	size = word_size(str, i);
	if (str[i] == '"' && str[i + size - 1] == '"')
		word = ft_substr(str, i + 1, size - 2);
	else
		word = ft_substr(str, i, size);
	if (!arr)
	{
		while (*arr--)
			free(*arr--);
		free(arr);
		return (NULL);
	}
	return (word);
}

char	**trim_input(char *input)
{
	int		words;
	int		i;
	int		w;
	char	**arr;

	if (!input)
		return (NULL);
	words = count_words(input);
	arr = (char **) malloc((words + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	w = -1;
	while (++w < words)
	{
		while (is_whitespace(input[i]))
			i++;
		arr[w] = get_word(arr + w, input, i);
		i += word_size(input, i);
	}
	arr[w] = 0;
	return (arr);
}
