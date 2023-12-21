/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:05:12 by digoncal          #+#    #+#             */
/*   Updated: 2023/06/20 13:06:26 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_strnlen(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

/*Modify or add a variables to env (var - variable / value - variable value)*/
char	**ms_setenv(char *var, char *value, char **env)
{
	char	*str;
	char	*tmp;
	int		i;

	i = -1;
	tmp = ft_strjoin(var, "=");
	str = ft_strjoin(tmp, value);
	free(tmp);
	while (env && env[++i])
	{
		if (!ft_strncmp(var, env[i], ft_strnlen(env[i], '=')))
		{
			free(env[i]);
			env[i] = ft_strdup(str);
			free(str);
			return (env);
		}
	}
	env = extend_arr(env, str);
	free(str);
	return (env);
}

/*Returns the value from the env's variable*/
char	*ms_getenv(char *var, char **env)
{
	char	*word;
	int		i;
	int		len;

	i = -1;
	while (env && env[++i])
	{
		if (!ft_strncmp(var, env[i], ft_strnlen(env[i], '=')))
		{
			word = ft_substr(env[i], 0, equal_sign(env[i]) - 1);
			len = ft_strlen(word);
			if (len < ft_strlen(var))
				len = ft_strlen(var);
			if (!ft_strncmp(var, word, len))
				return (free(word), ft_substr(env[i],
						ft_strnlen(env[i], '=') + 1, ft_strlen(env[i])));
			else
			{
				free(word);
				break ;
			}
		}
	}
	return (NULL);
}
