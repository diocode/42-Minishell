/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:51:00 by digoncal          #+#    #+#             */
/*   Updated: 2024/01/18 13:31:39 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_pid(void)
{
	t_process	*process;
	int			n_processes;

	process = ms()->process;
	n_processes = 0;
	while (process)
	{
		n_processes++;
		process = process->next;
	}
	if (!n_processes)
		return (1);
	ms()->pid = malloc(n_processes * sizeof(int));
	if (!ms()->pid)
		return (ms_error(1), 1);
	return (0);
}

static void	init_env_vars(char **av)
{
	char	*value;
	char	*n;

	value = getcwd(NULL, 0);
	ms_setenv("PWD", value);
	free(value);
	value = ms_getenv("SHLVL");
	if (!value || ft_atoi(value) <= 0)
		n = ft_strdup("1");
	else
		n = ft_itoa(ft_atoi(value) + 1);
	free(value);
	ms_setenv("SHLVL", n);
	free(n);
	value = ms_getenv("PATH");
	if (!value)
		ms_setenv("PATH", "/usr/local/sbin:/usr/local/bin:/usr/bin:/bin");
	free(value);
	value = ms_getenv("_");
	if (value)
		ms_setenv("_", av[0]);
	free(value);
}

t_env	*init_env(char **ev)
{
	t_env	*env;
	t_env	*tmp;
	int		i;

	env = NULL;
	i = -1;
	while (ev[++i])
	{
		tmp = malloc(sizeof(t_env));
		if (!tmp)
			return (ms_error(1), NULL);
		tmp->key = ft_substr(ev[i], 0, ft_strchr(ev[i], '=') - ev[i]);
		tmp->value = ft_substr(ev[i], ft_strchr(ev[i], '=') - ev[i] + 1,
				ft_strlen(ev[i]));
		tmp->next = env;
		env = tmp;
	}
	return (env);
}

void	init(char **av, char **ev)
{
	ft_bzero(ms(), sizeof(t_shell));
	ms()->env = init_env(ev);
	init_env_vars(av);
	ms()->lexer = NULL;
	ms()->process = NULL;
	ms()->input = NULL;
	ms()->pid = NULL;
	ms()->interact = false;
	ms()->heredoc = false;
	ms()->reset = false;
	ms()->quote[0] = false;
	ms()->quote[1] = false;
}
