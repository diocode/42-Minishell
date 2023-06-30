/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:35:48 by digoncal          #+#    #+#             */
/*   Updated: 2023/06/27 16:06:17 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

static void	ms_getpid(t_prompt *prompt)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0 || !pid)
	{
		if (pid < 0)
			ms_error(FORKERR, 1, NULL);
		free_array(prompt->env);
		exit(1);
	}
	waitpid(pid, NULL, 0);
	prompt->pid = pid - 1;
}

static t_prompt	*init_vars(t_prompt *prompt, char **av, char *value)
{
	char	*n;

	value = getcwd(NULL, 0);
	prompt->env = ms_setenv("PWD", value, prompt->env);
	free(value);
	value = ms_getenv("SHLVL", prompt->env);
	if (!value || ft_atoi(value) <= 0)
		n = ft_strdup("1");
	else
		n = ft_itoa(ft_atoi(value) + 1);
	free(value);
	prompt->env = ms_setenv("SHLVL", n, prompt->env);
	free(n);
	value = ms_getenv("PATH", prompt->env);
	if (!value)
		prompt->env = ms_setenv("PATH",
				"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", prompt->env);
	free(value);
	value = ms_getenv("_", prompt->env);
	if (value)
		prompt->env = ms_setenv("_", av[0], prompt->env);
	free(value);
	return (prompt);
}

/*Init prompt struct and setup env: PID - PWD - SHLVL - PATH - EXECUTABLE("_")*/
t_prompt	*init_prompt(char **av, char **ev)
{
	t_prompt	*prompt;
	char		*path;

	prompt = malloc(sizeof(t_prompt));
	if (!prompt)
		return (NULL);
	g_status = 0;
	path = NULL;
	prompt->lexer = malloc(sizeof(t_lexer));
	if (!prompt->lexer)
		return (NULL);
	prompt->simple_cmds = malloc(sizeof(t_simple_cmds));
	if (!prompt->simple_cmds)
		return (NULL);
	prompt->env = dup_arr(ev);
	ms_getpid(prompt);
	prompt = init_vars(prompt, av, path);
	return (prompt);
}
