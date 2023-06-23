/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdtrim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:00:12 by digoncal          #+#    #+#             */
/*   Updated: 2023/06/23 12:27:58 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* i[0] - i | i[1] - nbr words | i[2] - nbr quotes */
static int	count_words(char const *s)
{
	int	i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	while (s[i[0]])
	{
		if (s[i[0]] != ' ' && (s[i[0]] < 9 || s[i[0]] > 13) && i[2] % 2 == 0)
		{
			if (s[i[0]] == '"')
				i[2]++;
			i[1]++;
			while ((s[i[0]] != ' ' || i[2] % 2 != 0)
				&& (s[i[0]] < 9 || s[i[0]] > 13) && s[i[0]])
			{
				if (s[++i[0]] == '"')
					i[2]++;
				if (i[2] % 2 != 0 && (i[2] == total_quotes(s)))
					return (i[1]);
			}
		}
		else
			i[0]++;
	}
	return (i[1]);
}

static int	word_size(char const *str, int i)
{
	int	word_qts;
	int	quotes;
	int	len;

	word_qts = count_quotes(str, i);
	quotes = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			quotes++;
			if ((str[i + 1] == ' ' || (str[i + 1] >= 9 && str[i + 1] <= 13))
				&& ((word_qts % 2 == 0 && quotes == 2) || quotes == word_qts))
				break ;
		}
		else
		{
			if (!quotes && str[i] == ' ')
				break ;
			len++;
		}
		i++;
	}
	if (!len)
		return (1);
	if (quotes == 2)
	{
		if (str[i])
		{
			if (str[i] == '"')
				return (len);
		}
		else
		{
			if (str[i - 1] == '"')
				return (len);
		}
	}
	return (len + quotes);
}

static char	*get_word(char **arr, char *str, int i)
{
	char	*word;
	int		wsize;

	wsize = word_size(str, i);
	if (count_quotes(str, i) % 2 == 0 && str[i + 1 + wsize] == '"')
		word = ft_substr(str, i + 1, wsize);
	else
		word = ft_substr(str, i, wsize);
	printf("-WORD: {%s} (%d size)\n", word, wsize);
	if (!arr)
	{
		while (*arr--)
			free(*arr--);
		free(arr);
		return (NULL);
	}
	return (word);
}

char	**cdmtrim(char *input)
{
	int		nwords;
	int		i;
	int		j;
	char	**arr;

	if (!input)
		return (0);
	nwords = count_words(input);
	arr = (char **) malloc((nwords + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	j = -1;
	while (++j < nwords)
	{
		while (input[i] == ' ' || (input[i] >= 9 && input[i] <= 13))
			i++;
		arr[j] = get_word(arr + j, input, i);
		if (count_quotes(input, i) % 2 == 0 && input[i + 1 + word_size(input, i)] == '"')
			i += word_size(input, i) + 2;
		else
			i += word_size(input, i);
	}
	arr[j] = 0;
	return (arr);
}

/*
1 - FIX BUGS!
-> sdf "sdf

2 - CLEANUP CODE
*/
