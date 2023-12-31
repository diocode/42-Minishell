/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:35:48 by digoncal          #+#    #+#             */
/*   Updated: 2023/10/24 16:27:55 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_pid(t_prompt *prompt)
{
	t_simple_cmds	*process;
	int				n_processes;

	process = prompt->simple_cmds;
	n_processes = 0;
	while (process)
	{
		n_processes++;
		process = process->next;
	}
	if (!n_processes)
		return (1);
	prompt->pid = ft_calloc(n_processes, sizeof(int));
	if (!prompt->pid)
		return (ms_error(1));
	return (0);
}

t_simple_cmds	*init_simple_cmds(void)
{
	t_simple_cmds	*cmds;

	cmds = malloc(sizeof(t_simple_cmds));
	if (!cmds)
		return (NULL);
	cmds->str = NULL;
	cmds->builtin = NULL;
	cmds->redirct = NULL;
	cmds->num_redirct = 0;
	cmds->hd_file = NULL;
	cmds->next = NULL;
	cmds->prev = NULL;
	return (cmds);
}

void	init_vars(t_prompt *prompt, char **av, char *value)
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
}

void	init_flags(t_prompt *prompt)
{
	prompt->reset = false;
	prompt->interact = false;
	prompt->redict_flg = false;
	prompt->merge = false;
	prompt->no_node = false;
	prompt->separator = false;
	prompt->flg[0] = 0;
	prompt->flg[1] = 0;
	prompt->flg[2] = 0;
}

t_prompt	*init_prompt(char **av, char **ev)
{
	t_prompt	*prompt;
	char		*path;

	prompt = malloc(sizeof(t_prompt));
	if (!prompt)
		return (NULL);
	path = NULL;
	prompt->lexer = NULL;
	prompt->simple_cmds = NULL;
	prompt->heredoc = NULL;
	prompt->pid = NULL;
	prompt->exit_codes = NULL;
	init_flags(prompt);
	prompt->env = dup_arr(ev);
	init_vars(prompt, av, path);
	return (prompt);
}
