/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:57:39 by digoncal          #+#    #+#             */
/*   Updated: 2023/10/24 13:21:54 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

static int	var_len_after_dol(char *str, int j)
{
	int	i;

	i = j + 1;
	while (str[i] != '\0' && str[i] != '$' && str[i] != ' '
		&& str[i] != '\"' && str[i] != '\'' && str[i] != '=' && str[i] != '-'
		&& str[i] != ':')
		i++;
	return (i);
}

static int	replace_var(t_prompt *prompt, char *str, char **tmp, int i)
{
	int		j;
	int		len;
	char	*tmp2;
	char	*tmp3;

	j = -1;
	len = 0;
	while (prompt->env[++j])
	{
		if (!ft_strncmp(str + i + 1, prompt->env[j],
				equal_sign(prompt->env[j]) - 1)
			&& var_len_after_dol(str, i) - i == equal_sign(prompt->env[j]))
		{
			tmp2 = ft_strdup(prompt->env[j] + equal_sign(prompt->env[j]));
			tmp3 = ft_strjoin(*tmp, tmp2);
			free(*tmp);
			*tmp = tmp3;
			free(tmp2);
			len = equal_sign(prompt->env[j]);
		}
	}
	if (len == 0)
		len = var_len_after_dol(str, i) - i;
	return (len);
}

static char	*expand(t_prompt *prompt, char *str)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_strdup("\0");
	i = -1;
	while (str[++i])
	{
		i += if_digit(str, i);
		if (str[i] == '$' && str[i + 1] == '?')
			i += if_question_mark(prompt, &tmp);
		else if (str[i] == '$' && (str[i + 1] != ' ' && (str[i + 1] != '"'
					|| str[i + 2] != '\0')) && str[i + 1] != '\0')
			i += replace_var(prompt, str, &tmp, i);
		else
		{
			tmp2 = char_to_str(str[i]);
			tmp3 = ft_strjoin(tmp, tmp2);
			free(tmp);
			tmp = tmp3;
			free(tmp2);
		}
	}
	return (tmp);
}

char	*str_expander(t_prompt *prompt, char *str)
{
	char	*tmp;

	tmp = NULL;
	if (str[dollar_sign(str) - 2] != '\'' && dollar_sign(str) != 0
		&& str[dollar_sign(str)] != '\0')
	{
		tmp = expand(prompt, str);
		free(str);
		str = tmp;
	}
	str = delquotes(str, '\"');
	str = delquotes(str, '\'');
	return (str);
}

char	**single_cmd_expander(t_prompt *prompt, char **str)
{
	char	*tmp;
	int		i;

	i = -1;
	tmp = NULL;
	while (str[++i])
	{
		if (dollar_sign(str[i]) && str[i][dollar_sign(str[i]) - 2] != '\''
			&& dollar_sign(str[i]) != 0 && str[i][dollar_sign(str[i])] != '\0')
		{
			tmp = expand(prompt, str[i]);
			free(str[i]);
			str[i] = tmp;
		}
		if (ft_strncmp(str[0], "export", ft_strlen(str[0]) - 1))
		{
			str[i] = delquotes(str[i], '\"');
			str[i] = delquotes(str[i], '\'');
		}
	}
	return (str);
}
