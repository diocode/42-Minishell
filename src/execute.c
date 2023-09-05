/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 19:11:30 by digoncal          #+#    #+#             */
/*   Updated: 2023/07/25 14:18:42 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

void	handle_cmd(t_prompt *prompt, int id)
{
	t_simple_cmds	*process;

	process = prompt->simple_cmds;
	while (id--)
		process = prompt->simple_cmds->next;
	if (process->builtin)
	{
		if (!ft_strncmp(process->builtin, "echo", 4))
			printf("\033[0;32mECHO STILL LOADING\033[0m\n");
		if (!ft_strncmp(process->builtin, "env", 3))
			ms_env(prompt);
		if (!ft_strncmp(process->builtin, "pwd", 3))
			ft_printf("%s\n", ms_getenv("PWD", prompt->env));
		return ;
	}
}

//Handle single cmds that cannot be run in a child process
static int	single_cmd(t_prompt *prompt)
{
	char	*cmd;

	if (prompt->simple_cmds->builtin)
	{
		cmd = prompt->simple_cmds->builtin;
		if (!ft_strncmp(cmd, "exit", 4))
			exit_env(prompt);
		if (!ft_strncmp(cmd, "cd", 2))
			ms_cd(prompt, prompt->simple_cmds);
		if (!ft_strncmp(cmd, "export", 6))
			printf("\033[0;32mEXPORT STILL LOADING\033[0m\n");
		if (!ft_strncmp(cmd, "unset", 5))
			printf("\033[0;32mUNSET STILL LOADING\033[0m\n");
		handle_cmd(prompt, 0);
		return (0);
	}
	return (1);
}

void	execute(t_prompt *prompt)
{
	t_simple_cmds	*process;
	int				n_pipes;
	int				end[2];

	if (!prompt->simple_cmds->next && single_cmd(prompt))
		return ;
	process = prompt->simple_cmds;
	n_pipes = 0;
	while (process)
	{
		n_pipes++;
		replace_variables(prompt, process);
		if (process->next)
			pipe(end);
		if (send_heredoc(prompt, process))
			return ;
		process = process->next;
	}
}
