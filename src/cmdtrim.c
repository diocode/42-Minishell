/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdtrim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:00:12 by digoncal          #+#    #+#             */
/*   Updated: 2023/06/21 18:13:41 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_quotes(char const *str)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (str[i])
	{
		if (str[i++] == '"')
			quotes++;
	}
	return (quotes);
}

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
				if (i[2] % 2 != 0 && (i[2] == count_quotes(s)))
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
	int	len;
	int	flg;

	len = 0;
	flg = 0;
	while (str[i] != ' ' && (str[i] < 9 || str[i] > 13) && str[i])
	{
		if (str[i] == '"')
			flg = 1;
		i++;
		len++;
	}
	return (len);
}

static char	*get_word(char **arr, char *str, int i)
{
	char	*word;
	int		wsize;

	wsize = word_size(str, i);
	word = ft_substr(str, i, wsize);
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
		i += word_size(input, i);
	}
	arr[j] = 0;
	return (arr);
	/*ADD THE EXCEPTION FOR THE "" IN THE SPLIT PROCESS*/
}
