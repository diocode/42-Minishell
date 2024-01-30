/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:04:12 by digoncal          #+#    #+#             */
/*   Updated: 2024/01/18 17:04:12 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_code;

int	count_pipes(t_token *lx)
{
	t_token	*tmp;
	int		pipes;

	tmp = lx;
	pipes = 0;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, "|", 2)
			|| !ft_strncmp(tmp->content, "||", 3))
			pipes++;
		tmp = tmp->next;
	}
	return (pipes);
}

bool	solo_doll_sign(const char *str)
{
	int	i;
	int	doll;

	doll = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
			doll++;
		if (str[i] != '\'' && str[i] != '\"' && str[i] != '$')
			return (false);
	}
	if (doll > 1)
		return (false);
	return (true);
}

int	builtin(t_process *process)
{
	char	*cmd;
	int		status;

	status = 1;
	cmd = process->builtin;
	if (!ft_strncmp(cmd, "exit", 5))
		return (ms_exit(process));
	else if (!ft_strncmp(cmd, "cd", 3))
		status = ms_cd(process);
	else if (!ft_strncmp(cmd, "export", 7))
		status = ms_export(process);
	else if (!ft_strncmp(cmd, "unset", 6))
		status = ms_unset(process);
	else if (!ft_strncmp(cmd, "echo", 5))
		status = ms_echo(process);
	else if (!ft_strncmp(cmd, "env", 4))
		status = ms_env(false);
	else if (!ft_strncmp(cmd, "pwd", 4))
		status = ms_pwd();
	return (status);
}
