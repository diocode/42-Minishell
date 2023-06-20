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

extern int	g_status;

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
	int		i;

	i = -1;
	while (env && env[++i])
	{
		if (!ft_strncmp(var, env[i], ft_strnlen(env[i], '=')))
			return (ft_substr(env[i], ft_strnlen(env[i], '=') + 1,
					ft_strlen(env[i])));
	}
	return (NULL);
}
