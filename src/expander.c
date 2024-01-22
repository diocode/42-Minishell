/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:23:55 by digoncal          #+#    #+#             */
/*   Updated: 2024/01/22 16:15:10 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_code;

static char *create_newstr(char *str, size_t i, char *key, char *value)
{
	char	*new_str;
	size_t	size;

	size = i + ft_strlen(value) + ft_strlen(str + i + ft_strlen(key)) + 1;
	new_str = ft_calloc(size, sizeof(char));
	if (!new_str)
		return (ms_error(1), NULL);
	strncpy(new_str, str, i);
	strcat(new_str, value);
	strcat(new_str, str + i + ft_strlen(key));
	free(str);
	return (new_str);
}

static int expand_str(t_token *lx, size_t i)
{
	char 	*key;
	char	*value;
	size_t	len;
	size_t 	j;

	if (ft_strlen(lx->content) < 2)
		return (1);
	len = 1;
	while (lx->content[i + len] && (isalnum(lx->content[i + len]) || lx->content[i + len] == '_' || lx->content[i + len] == '?'))
	{
		len++;
		if (lx->content[i + len - 1] == '?')
			break ;
	}
	key = ft_calloc(len + 1, sizeof(char));
	if (!key)
		return (ms_error(1), 1);
	printf("STR: %s\n", lx->content);
	ft_strlcpy(key, lx->content + i + 1, len);
	printf("LEN: %ld\n", len);
	printf("KEY pointer: %s\n", lx->content + i + 1);
	printf("KEY: %s\n",key);
	j = 0;
	while (j < len && isdigit(key[j]))
		j++;
	if (j > 0)
	{
		ft_memmove(key, key + 1, len - 1);
		ft_memmove(lx->content + i, key, ft_strlen(key));
		ft_memmove(lx->content + i + ft_strlen(key), lx->content + i + len, ft_strlen(lx->content + i + len) + 1);
	}
	else
	{
		value = NULL;
		if (!ft_strncmp(key, "?", 2))
			value = ft_itoa(g_exit_code);
		else
			value = ms_getenv(key);
		if (value)
		{
			if ((ft_strlen(value) + ft_strlen(lx->content) - ft_strlen(key) - 1) > ft_strlen(lx->content))
				lx->content = create_newstr(lx->content, i, key, value);
			else
			{
				ft_memmove(lx->content + i, value, ft_strlen(value));
				ft_memmove(lx->content + i + ft_strlen(value), lx->content + i + len, ft_strlen(lx->content + i + len) + 1);
			}
			free(value);
		}
		else
			ft_memmove(lx->content + i, lx->content + i + len, ft_strlen(lx->content + i + len) + 1);
	}
	free(key);
	return (0);
}

static bool check_heredoc(char *str, size_t i)
{
	char *heredoc_pos;

	heredoc_pos = ft_strnstr(str, "<<", ft_strlen(str));
	if (i > 0 && str[i - 1] == '\"' && heredoc_pos
		&& heredoc_pos < str + i - 1)
		return false;
	else if (i > 0 && str[i - 1] == '\"')
		return true;
	else if (heredoc_pos && heredoc_pos < str + i)
		return false;
	else
		return true;
}

static void expand(t_token *lexer)
{
	int	i;

	ms()->quote[0] = false;
	ms()->quote[1] = false;
	i = -1;
	while (lexer->content[++i])
	{
		in_quotes(lexer->content[i]);
		if (lexer->content[i] == '$' && !ms()->quote[0]
			&& (!lexer->prev || lexer->prev->type != HEREDOC))
			if (check_heredoc(lexer->content, i))
			{
				if (expand_str(lexer, i))
					continue ;
				i = -1;
			}
	}
}

int expander(void)
{
	t_token		*tmp;

	tmp = ms()->lexer;
	while (tmp)
	{
		if (valid_quotes(tmp->content))
			expand(tmp);
		tmp = tmp->next;
	}
	return (0);
}
