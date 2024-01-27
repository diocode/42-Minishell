/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:07:30 by digoncal          #+#    #+#             */
/*   Updated: 2024/01/26 18:07:30 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_code;

static int	builtin(t_process *process)
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
	/*else if (!ft_strncmp(cmd, "echo", 5))
		status = ms_echo(process);*/
	else if (!ft_strncmp(cmd, "env", 4))
		status = ms_env(false);
	else if (!ft_strncmp(cmd, "pwd", 4))
		status = ms_pwd();
	return (status);
}

static void	single_cmd(t_process *process)
{
	char	*cmd;
	//int		status;
	//int		pid;

	//status = 0;
	cmd = process->builtin;
	if (cmd && (!ft_strncmp(cmd, "exit", 5) || !ft_strncmp(cmd, "cd", 3)
		|| !ft_strncmp(cmd, "export", 7) || !ft_strncmp(cmd, "unset", 6)))
	{
		g_exit_code = builtin(process);
		return ;
	}
	if (!ft_strncmp(cmd, "env", 4))
	{
		g_exit_code = builtin(process);
		return ;
	}
	/*send_heredoc(prompt, prompt->simple_cmds);
	pid = fork();
	if (pid < 0)
		ms_error(5);
	if (pid == 0)
		handle_cmd(prompt, prompt->simple_cmds);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	return (0);*/
}

void execute(void)
{
	t_process	*process;
	//int			end[2];
	//int			fd_in;

	//fd_in = STDIN_FILENO;
	process = ms()->process;
	if (!process->next)
		return (single_cmd(process));
}
