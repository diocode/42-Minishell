/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:57:39 by digoncal          #+#    #+#             */
/*   Updated: 2023/09/06 15:22:31 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

int	loop_if_dollar_sign(t_tools *tools, char *str, char **tmp, int j)
{
	int		k;
	int		ret;
	char	*tmp2;
	char	*tmp3;

	k = 0;
	ret = 0;
	while (tools->envp[k])
	{
		if (ft_strncmp(str + j + 1, tools->envp[k],
					   equal_sign(tools->envp[k]) - 1) == 0
			&& after_dol_lenght(str, j) - j == (int)equal_sign(tools->envp[k]))
		{
			tmp2 = ft_strdup(tools->envp[k] + equal_sign(tools->envp[k]));
			tmp3 = ft_strjoin(*tmp, tmp2);
			free(*tmp);
			*tmp = tmp3;
			free(tmp2);
			ret = equal_sign(tools->envp[k]);
		}
		k++;
	}
	if (ret == 0)
		ret = after_dol_lenght(str, j) - j;
	return (ret);
}

static char	*detect_dollar_sign(t_prompt *prompt, char *str)
{
	int		i;
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_strdup("\0");
	i = 0;
	while (str[i])
	{
		j = i;
		if (str[j] == '$')
			if (ft_isdigit(str[j + 1]) == 1)
				j += 2;
		i += j - i;
		if (str[i] == '$' && str[i + 1] == '?')
		{
			free(tmp);
			tmp = ft_itoa(prompt->heredoc->error_num);
			i += ft_strlen(tmp) + 1;
		}
		else if (str[i] == '$' && (str[i + 1] != ' ' && (str[i + 1] != '"'
					|| str[i + 2] != '\0')) && str[i + 1] != '\0')
			i += loop_if_dollar_sign(tools, str, &tmp, i);
		else
		{
			tmp2 = char_to_str(str[i++]);
			tmp3 = ft_strjoin(tmp, tmp2);
			free(tmp);
			tmp = tmp3;
			free(tmp2);
		}
	}
	return (tmp);
}

static size_t	dollar_sign(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i + 1);
		i++;
	}
	return (0);
}

char	*str_expander(t_prompt *prompt, char *str)
{
	char	*tmp;

	tmp = NULL;
	if (str[dollar_sign(str) - 2] != '\'' && dollar_sign(str) != 0
		&& str[dollar_sign(str)] != '\0')
	{
		tmp = detect_dollar_sign(prompt, str);
		free(str);
		str = tmp;
	}
	str = delquotes(str, '\"');
	str = delquotes(str, '\'');
	return (str);
}
