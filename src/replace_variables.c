/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:16:19 by digoncal          #+#    #+#             */
/*   Updated: 2023/07/25 15:16:19 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

char	*get_env(t_prompt *prompt, char *val)
{
	int		i[3];

	if (!val)
		return (NULL);
	i[0] = -1;
	while (prompt->env[++i[0]])
	{
		if (!ft_strncmp(val, prompt->env[i[0]], ft_strlen(val)))
		{
			free(val);
			i[1] = 0;
			while (prompt->env[i[0]][i[1]] != '=')
				i[1]++;
			val = ft_calloc(ft_strlen(prompt->env[i[0]]) - i[1] + 1,
					sizeof(char));
			if (!val)
				return (NULL);
			i[2] = -1;
			while (prompt->env[i[0]][i[1]])
				val[++i[2]] = prompt->env[i[0]][++i[1]];
			return (val);
		}
	}
	free(val);
	return (NULL);
}

static char	*get_variable(t_simple_cmds *process, int word, int i)
{
	char	*val;
	int		start;
	int		j;

	start = i;
	j = 0;
	while (process->str[word][i] && process->str[word][i] != ' ')
		i++;
	val = ft_calloc(i - start + 1, sizeof(char));
	if (!val)
		return (NULL);
	while (process->str[word][start] && process->str[word][start] != ' ')
		val[j++] = process->str[word][start++];
	return (val);
}

void	replace_variables(t_prompt *prompt, t_simple_cmds *process)
{
	char	*val;
	int		i;
	int		j;

	i = -1;
	while (process->str[++i])
	{
		j = -1;
		while (process->str[i] && process->str[i][++j])
		{
			if (process->str[i][j] && process->str[i][j] == '$')
			{
				val = get_env(prompt, get_variable(process, i, j + 1));
				if (val)
				{
					free(process->str[i]);
					process->str[i] = val;
					return ;
				}
			}
		}
	}
}
