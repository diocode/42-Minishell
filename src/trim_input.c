/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:03:44 by digoncal          #+#    #+#             */
/*   Updated: 2023/06/25 18:35:08 by logname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*Checks: More 1 quote || All existing quotes form a single word*/
static int	check_quotes(char const *str)
{
	int	i;
	int	flg;
	int	total_quotes;

	i = -1;
	flg = 0;
	total_quotes = 0;
	while (str[++i])
	{
		if (str[i] == '"')
		{
			total_quotes++;
			if (str[i + 1] == ' ' || str[i - 1] == ' ')
				flg++;
		}
	}
	if (total_quotes < 2 || !flg)
		return (1);
	return (0);
}

static int	is_whitespace(char c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

static int	prev_quotes(char const *str, int end)
{
	int	i;
	int	quotes;

	i = -1;
	quotes = 0;
	while (++i < end)
	{
		if (str[i] == '"')
			quotes++;
	}
	return (quotes);
}

static int	word_size(char *str, int i)
{
	int	size;

	size = 0;
	while (str[i])
	{
		if (str[i] == '"' && (prev_quotes(str, i) % 2 != 0
				|| !prev_quotes(str, i + size)))
		{
			i++;
			while (str[i] != '"')
			{
				size++;
				i++;
			}
			return (size);
		}
		if (!is_whitespace(str[i]))
			size++;
		else
			break ;
		i++;
	}
	if (!size)
		return (1);
	return (size);
}

static int	count_words(char const *str)
{
	int	i;
	int	words;

	words = 0;
	i = -1;
	while (str[++i])
	{
		if (!is_whitespace(str[i]))
		{
			words++;
			if (str[i] == '"')
			{
				if (prev_quotes(str, i) % 2 != 0)
					words--;
			}
			while (!is_whitespace(str[i]) && str[i])
			{
				i++;
			}
		}
		if (!str[i])
			break ;
	}
	return (words);
}

static char	*get_word(char *str, int i)
{
	int		size;

	size = word_size(str, i);
	if (is_whitespace(str[i + size])
		&& str[i + size + 1] != '"' && (prev_quotes(str, i + size) % 2 != 0
			|| !prev_quotes(str, i + size)))
		return (ft_substr(str, i, size));
	else
		return (ft_substr(str, i + 1, size));
}

char	**trim_input(char *input)
{
	char	**arr;
	int		i;
	int		w;
	int		size;

	if (!input)
		return (0);
	arr = NULL;
	if (check_quotes(input))
	{
		if (!ft_strncmp(input, "\"\"", 4))
		{
			arr = ft_calloc(sizeof(char *), 1);
			if (!arr)
				return (NULL);
		}
		else
			arr = ft_split(input, ' ');
		return (arr);
	}
	arr = (char **) malloc((count_words(input) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	w = -1;
	i = 0;
	while (++w < count_words(input))
	{
		while (is_whitespace(input[i]))
			i++;
		arr[w] = get_word(input, i);
		size = word_size(input, i);
		if (is_whitespace(input[i + size])
			&& (prev_quotes(input, i + size) % 2 != 0
				|| !prev_quotes(input, i + size)))
			i += size;
		else
			i += size + 2;
	}
	arr[w] = 0;
	return (arr);
}

/* - CHECK FOR BUGS / FIX BUGS!!
 * - USE THE STR IN THE NOTES
 * - WORD_SIZE SHOULD BE WORKING
 * - FINISH UP TRIM_INPUT
 * */
