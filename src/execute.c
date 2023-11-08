/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 19:11:30 by digoncal          #+#    #+#             */
/*   Updated: 2023/10/20 11:58:34 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

static int	dup_process(t_prompt *p, t_simple_cmds *cmd, int fd_in, int end[2])
{
	if (cmd->prev && dup2(fd_in, STDIN_FILENO) < 0)
		return (1);
	close(end[0]);
	if (cmd->next && dup2(end[1], STDOUT_FILENO) < 0)
		return (1);
	close(end[1]);
	if (cmd->prev)
		close(fd_in);
	handle_cmd(p, cmd);
	return (0);
}

static int	check_fd(t_prompt *prompt, t_simple_cmds *process, int end[2])
{
	int	fd_in;

	if (prompt->heredoc->status)
	{
		close(end[0]);
		fd_in = open(process->hd_file, O_RDONLY);
	}
	else
		fd_in = end[0];
	return (fd_in);
}

static int	fork_process(t_prompt *p, t_simple_cmds *cmd, int fd_in, int end[2])
{
	static int	i;

	if (!i)
		i = 0;
	if (p->reset == true)
	{
		i = 0;
		p->reset = false;
	}
	p->pid[i] = fork();
	if (p->pid[i] < 0)
		return (ms_error(5));
	if (p->pid[i] == 0)
		if (dup_process(p, cmd, fd_in, end))
			return (ms_error(4));
	i++;
	return (0);
}

static void	wait_pipe(t_prompt *prompt, int *pid)
{
	t_simple_cmds	*process;
	int				n_pipes;
	int				i;
	int				status;

	process = prompt->simple_cmds;
	n_pipes = 0;
	while (process)
	{
		n_pipes++;
		process = process->next;
	}
	i = -1;
	while (++i < n_pipes - 1)
		waitpid(pid[i], &status, 0);
	waitpid(pid[i], &status, 0);
	if (WIFEXITED(status))
		prompt->heredoc->error_num += WEXITSTATUS(status);
}

int	execute(t_prompt *prompt)
{
	t_simple_cmds	*process;
	int				end[2];
	int				fd_in;

	fd_in = STDIN_FILENO;
	process = prompt->simple_cmds;
	if (!process->next)
		return (single_cmd(prompt, process));
	while (process)
	{
		if (process->next)
			pipe(end);
		if (send_heredoc(prompt, process))
			return (1);
		if (fork_process(prompt, process, fd_in, end))
			return (1);
		close(end[1]);
		if (process->prev)
			close(fd_in);
		fd_in = check_fd(prompt, process, end);
		process = process->next;
	}
	wait_pipe(prompt, prompt->pid);
	return (0);
}
