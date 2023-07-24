/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 19:11:30 by digoncal          #+#    #+#             */
/*   Updated: 2023/07/23 20:08:25 by logname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

//Handle single cmds that cannot be run in a separate process
static int	single_cmd(t_prompt *prompt)
{
	char	*cmd;

	if (prompt->simple_cmds->builtin)
	{
		cmd = prompt->simple_cmds->builtin;
		if (!ft_strncmp(cmd, "exit", 4))
			exit_env(prompt);
		if (!ft_strncmp(cmd, "cd", 2))
			ms_cd(prompt);
		if (!ft_strncmp(cmd, "export", 6))
			printf("\033[0;32mEXPORT STILL LOADING\033[0m\n");
		if (!ft_strncmp(cmd, "unset", 5))
			printf("\033[0;32mUNSET STILL LOADING\033[0m\n");
		return (0);
	}
	return (1);
}

void	execute(t_prompt *prompt)
{
	t_simple_cmds	*process;

	if (!prompt->simple_cmds->next && single_cmd(prompt))
		return ;
	process = prompt->simple_cmds;
	while (process)
	{
		//create child process for each process (expander->heredoc->fork->set env->handle cmd)
		process = process->next;
	}
}
