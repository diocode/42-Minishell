/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:22:58 by digoncal          #+#    #+#             */
/*   Updated: 2023/07/04 17:45:32 by digoncal         ###   ########.fr       */
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
static int	wd_size(t_prompt *p, char const *str, int i)
{
	int	len;

	len = 0;
	p->flg[0] = 0;
	p->flg[1] = 0;
	while (str[i] && !(is_whitespace(str[i]) && !p->flg[0] && !p->flg[1]))
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			check_flg(p, str, i);
			if ((str[i] == '"' && p->flg[1]) || (str[i] == '\'' && p->flg[0]))
				len++;
			i++;
		}
		else
		{
			i++;
			len++;
		}
		if ((p->flg[0] && !next_quote(str, i, '"', p->flg[0])))
			p->flg[0] = 0;
		if ((p->flg[1] && !next_quote(str, i, '\'', p->flg[1])))
			p->flg[1] = 0;
	}
	return (len);
}

static char	*get_word(t_prompt *p, char *str, int i, int size)
{
	char	*word;
	int		j;

	word = ft_calloc(size + 1, sizeof(char));
	if (!word)
		return (NULL);
	j = 0;
	while (str[i] && !(is_whitespace(str[i]) && !p->flg[0] && !p->flg[1]))
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			check_flg(p, str, i);
			if ((str[i] == '"' && p->flg[1]) || (str[i] == '\'' && p->flg[0]))
				word[j++] = str[i];
			i++;
		}
		else
			word[j++] = str[i++];
		if ((p->flg[0] && !next_quote(str, i, '"', p->flg[0])))
			p->flg[0] = 0;
		if ((p->flg[1] && !next_quote(str, i, '\'', p->flg[1])))
			p->flg[1] = 0;
	}
	return (word);
}

/* flg[0] = '"' | flg[1] = '\'' */
static int	count_words(t_prompt *prompt, char const *str)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		prompt->flg[0] = 0;
		prompt->flg[1] = 0;
		if (!is_whitespace(str[i]))
		{
			words++;
			if (str[i] == '"')
				prompt->flg[0] = 1;
			if (str[i] == '\'')
				prompt->flg[1] = 1;
			i = skip_word(prompt, str, i);
		}
		else
			i++;
	}
	return (words);
}

/* flg[0] = '"' | flg[1] = '\'' */
char	**trim_input(t_prompt *p, char *input)
{
	int		words;
	int		i;
	int		w;
	char	**arr;

	if (!input)
		return (NULL);
	words = count_words(p, input);
	arr = (char **) malloc((words + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	w = -1;
	while (++w < words)
	{
		while (is_whitespace(input[i]))
			i++;
		arr[w] = get_word(p, input, i, wd_size(p, input, i));
		i += wd_size(p, input, i) + qts_nbr(p, input, i, wd_size(p, input, i));
		p->flg[0] = 0;
		p->flg[1] = 0;
	}
	arr[w] = 0;
	free(input);
	return (arr);
}
