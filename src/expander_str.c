/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:00:46 by digoncal          #+#    #+#             */
/*   Updated: 2024/01/23 13:00:46 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_code;

static char	*create_newstr(char *str, size_t i, char *key, char *value)
{
	char	*new_str;
	size_t	size;

	size = i + ft_strlen(value) + ft_strlen(str + i + ft_strlen(key)) + 1;
	new_str = ft_calloc(size, sizeof(char));
	if (!new_str)
		return (ms_error(1), NULL);
	ft_strlcpy(new_str, str, i + 1);
	ft_strcat(new_str, value);
	ft_strcat(new_str, str + i + ft_strlen(key) + 1);
	free(str);
	return (new_str);
}

static void	expand_handle_value(t_token *lx, size_t i, char *key, size_t len)
{
	char	*value;

	value = NULL;
	if (!ft_strncmp(key, "?", 2))
		value = ft_itoa(g_exit_code);
	else
		value = ms_getenv(key);
	if (value)
	{
		lx->content = create_newstr(lx->content, i, key, value);
		free(value);
	}
	else
		ft_memmove(lx->content + i, lx->content + i + len,
			ft_strlen(lx->content + i + len) + 1);
}

static void	expand_handle_key(t_token *lx, size_t i, char *key, size_t len)
{
	size_t	j;

	j = 0;
	while (j < len && isdigit(key[j]))
		j++;
	if (j > 0)
	{
		ft_memmove(key, key + 1, len - 1);
		ft_memmove(lx->content + i, key, ft_strlen(key));
		ft_memmove(lx->content + i + ft_strlen(key),
			lx->content + i + len, ft_strlen(lx->content + i + len) + 1);
	}
	else
		expand_handle_value(lx, i, key, len);
}

int	expand_str(t_token *lx, size_t i)
{
	char	*key;
	size_t	len;

	len = 1;
	if (ft_strlen(lx->content) < 2 || is_whitespace(lx->content[i + len])
		|| solo_doll_sign(lx->content))
		return (1);
	while (lx->content[i + len] && (isalnum(lx->content[i + len])
			|| lx->content[i + len] == '_' || lx->content[i + len] == '?'))
	{
		len++;
		if (lx->content[i + len - 1] == '?')
			break ;
	}
	key = ft_calloc(len + 1, sizeof(char));
	if (!key)
		return (ms_error(1), 1);
	ft_strlcpy(key, lx->content + i + 1, len);
	expand_handle_key(lx, i, key, len);
	free(key);
	return (0);
}
