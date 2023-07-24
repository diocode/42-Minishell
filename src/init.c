/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:35:48 by digoncal          #+#    #+#             */
/*   Updated: 2023/07/12 18:24:33 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

t_simple_cmds	*init_simple_cmds(void)
{
	t_simple_cmds	*cmds;

	cmds = malloc(sizeof(t_simple_cmds));
	if (!cmds)
		return (NULL);
	cmds->str = NULL;
	cmds->builtin = NULL;
	cmds->file = NULL;
	cmds->redirct = NULL;
	cmds->num_redirct = 0;
	cmds->next = NULL;
	cmds->prev = NULL;
	return (cmds);
}

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
	prompt->lexer = NULL;
	prompt->simple_cmds = init_simple_cmds();
	prompt->env = dup_arr(ev);
	ms_getpid(prompt);
	prompt = init_vars(prompt, av, path);
	prompt->flg[0] = 0;
	prompt->flg[1] = 0;
	return (prompt);
}
