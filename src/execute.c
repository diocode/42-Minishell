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

static int	dup_process(t_process *process, int fd_in, int end[2])
{
	if (process->prev && dup2(fd_in, STDIN_FILENO) < 0)
		return (1);
	close(end[0]);
	if (process->next && dup2(end[1], STDOUT_FILENO) < 0)
		return (1);
	close(end[1]);
	if (process->prev)
		close(fd_in);
	handle_cmd(process);
	return (0);
}

static int	check_fd(t_process *process, int end[2])
{
	int	fd_in;

	fd_in = end[0];
	if (ms()->heredoc)
	{
		close(end[0]);
		if (process->hd_file)
			fd_in = open(process->hd_file, O_RDONLY);
	}
	return (fd_in);
}

static int	fork_process(t_process *process, int fd_in, int end[2])
{
	static int	i;

	if (!i)
		i = 0;
	if (ms()->reset == true)
	{
		i = 0;
		ms()->reset = false;
	}
	ms()->pid[i] = fork();
	if (ms()->pid[i] < 0)
		return (ms_error(5), 1);
	if (ms()->pid[i] == 0)
		if (dup_process(process, fd_in, end))
			return (ms_error(4), 1);
	i++;
	return (0);
}

static void	wait_pipe(int *pid)
{
	t_process	*process;
	int			n_pipes;
	int			i;
	int			status;

	process = ms()->process;
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
		g_exit_code = WEXITSTATUS(status);
}

void	execute(void)
{
	t_process	*process;
	int			end[2];
	int			fd_in;

	fd_in = STDIN_FILENO;
	process = ms()->process;
	if (!process->next)
		return (single_cmd(process));
	while (process)
	{
		if (process->next)
			pipe(end);
		if (send_heredoc(process))
			return ;
		if (fork_process(process, fd_in, end))
			return ;
		close(end[1]);
		if (process->prev)
			close(fd_in);
		fd_in = check_fd(process, end);
		process = process->next;
	}
	wait_pipe(ms()->pid);
}
