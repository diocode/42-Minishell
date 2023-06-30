/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:22:58 by digoncal          #+#    #+#             */
/*   Updated: 2023/06/30 17:07:46 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	next_quote(char const *str, int i, char c, int flg)
{
	while (str[i] && !(is_whitespace(str[i]) && !flg))
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/* flg[0] = '"' | flg[1] = '\'' */
static int	word_size(char const *str, int i)
{
	int	len;
	int	flg[2];

	len = 0;
	flg[0] = 0;
	flg[1] = 0;
	while (str[i] && !(is_whitespace(str[i]) && !flg[0] && !flg[1]))
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (str[i] == '"')
			{
				if (flg[0])
					flg[0] = 0;
				else if (!flg[1])
					flg[0] = 1;
			}
			if (str[i] == '\'')
			{
				if (flg[1])
					flg[1] = 0;
				else if (!flg[0])
					flg[1] = 1;
			}
			if ((str[i] == '"' && flg[1]) || (str[i] == '\'' && flg[0]))
				len++;
			i++;
		}
		else
		{
			i++;
			len++;
		}
		if ((flg[0] && !next_quote(str, i, '"', flg[0])))
			flg[0] = 0;
		if ((flg[1] && !next_quote(str, i, '\'', flg[1])))
			flg[1] = 0;
	}
	/*SILL HERE!!!! TEST WITH  - "123 "45'6 ""7" - */
	return (len);
}

static char	*get_word(char **arr, char *str, int i)
{
	char	*word;
	int		size;

	size = word_size(str, i);
	printf("WORD: %d size\n", size);
	if ((str[i] == '"' && str[i + size - 1] == '"')
		|| (str[i] == '\'' && str[i + size - 1] == '\''))
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

/* flg[0] = '"' | flg[1] = '\'' */
static int	count_words(char const *str)
{
	int	i;
	int	words;
	int	flg[2];

	i = 0;
	words = 0;
	while (str[i])
	{
		flg[0] = 0;
		flg[1] = 0;
		if (!is_whitespace(str[i]))
		{
			words++;
			if (str[i] == '"')
				flg[0] = 1;
			if (str[i] == '\'')
				flg[1] = 1;
			while ((!is_whitespace(str[i]) || flg[0] || flg[1]) && str[i])
			{
				i++;
				if (str[i] == '"' && flg[0] /*&& is_whitespace(str[i + 1])*/)
					flg[0] = 0;
				if (str[i] == '\'' && flg[1] /*&& is_whitespace(str[i + 1])*/)
					flg[1] = 0;
			}
		}
		else
			i++;
	}
	printf("WORDS: %d\n", words);
	return (words);
}

/*IF ODD  QUOTES -> LAST QUOTE TAKEN AS A NORMAL CHAR*/
/* flg[0] = '"' | flg[1] = '\'' */
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
	free(input);
	return (arr);
}

/*
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
			if (str[i] == '"' || str[i] == '\'')
				flg = 1;
			while ((!is_whitespace(str[i]) || flg) && str[i])
			{
				i++;
				if (str[i] == '"' || str[i] == '\'' || next_quote(str, i))
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
	if (str[i] == '"' || str[i] == '\'')
	{
		flg = 1;
		len++;
		i++;
	}
	while ((!is_whitespace(str[i]) || flg) && str[i])
	{
		if (str[i] == '"' || str[i] == '\'' || next_quote(str, i))
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
	if ((str[i] == '"' && str[i + size - 1] == '"')
		|| (str[i] == '\'' && str[i + size - 1] == '\''))
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
	free(input);
	return (arr);
}

static int	next_quote(char const *str, int i, char c)
{
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

==============================================================================


*/
/* flg[0] = '"' | flg[1] = '\'' *//*


static int	word_size(char const *str, int i)
{
	int	len;
	int	flg[2];

	len = 0;
	flg[0] = 0;
	flg[1] = 0;
	if (str[i] == '"')
		flg[0] = 1;
	if (str[i] == '\'')
		flg[1] = 1;
	if (str[i] == '"' || str[i] == '\'')
	{
		i++;
		len++;
	}
	while ((flg[0] || flg[1]) && str[i])
	{
		if (str[i] == '"' || ((!next_quote(str, i, '"') && flg[0])))
			flg[0] = 0;
		if (str[i] == '\'' || (!next_quote(str, i, '\'') && flg[1]))
			flg[1] = 0;
		len++;
		i++;
	}
	//printf("WORD: %d size\n", len);
	return (len);
}


static char	*get_word(char **arr, char *str, int i)
{
	char	*word;
	int		size;

	size = word_size(str, i);
	if ((str[i] == '"' && str[i + size - 1] == '"')
		|| (str[i] == '\'' && str[i + size - 1] == '\''))
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

*/
/* flg[0] = '"' | flg[1] = '\'' *//*


static int	count_words(char const *str)
{
	int	i;
	int	words;
	int	flg[2];

	i = 0;
	words = 0;
	while (str[i])
	{
		flg[0] = 0;
		flg[1] = 0;
		if (!is_whitespace(str[i]))
		{
			words++;
			if (str[i] == '"')
				flg[0] = 1;
			if (str[i] == '\'')
				flg[1] = 1;
			if (flg[0] || flg[1])
			{
				while ((flg[0] || flg[1]) && str[i])
				{
					i++;
					if ((str[i] == '"' && !flg[1]) || ((!next_quote(str, i, '"') && flg[0])))
					{
						flg[0] = 0;
						i++;
					}
					if ((str[i] == '\'' && !flg[0]) || (!next_quote(str, i, '\'') && flg[1]))
					{
						flg[1] = 0;
						i++;
					}
				}
			}
			else
				while (!is_whitespace(str[i]) && str[i])
					i++;

		}
		else
			i++;
	}
	printf("WORDS: %d\n", words);
	return (words);
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
	free(input);
	return (arr);
}

static int	next_quote(char const *str, int i)
{
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}
*/
