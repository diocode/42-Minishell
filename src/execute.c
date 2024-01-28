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
	else if (!ft_strncmp(cmd, "echo", 5))
		status = ms_echo(process);
	else if (!ft_strncmp(cmd, "env", 4))
		status = ms_env(false);
	else if (!ft_strncmp(cmd, "pwd", 4))
		status = ms_pwd();
	return (status);
}

static char	**get_paths(void)
{
	char	*path;
	char	*tmp;
	char	**paths;
	int		i;

	path = ms_getenv("PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	free(path);
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = tmp;
	}
	return (paths);
}

static int	system_cmd(t_process *process)
{
	char	*path;
	char	**paths;
	int		i;

	if (!access(process->args[0], F_OK))
		execve(process->args[0], process->args, ms()->tmp_env);
	paths = get_paths();
	if (!paths)
		return (error_cmd_not_found(process));
	i = -1;
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], process->args[0]);
		if (!access(path, F_OK))
			execve(path, process->args, ms()->tmp_env);
		free(path);
	}
	free_array(paths);
	return (error_cmd_not_found(process));
}

static void	exit_cmd(void)
{
	free_data(false);
	exit(1);
}

int	handle_cmd(t_process *process)
{
	if (process->redirect)
		if (setup_redirect(process))
			exit_cmd();
	if (process->builtin)
	{
		g_exit_code = builtin(process);
		free_data(false);
		exit(g_exit_code);
	}
	if (process->args && process->args[0])
		g_exit_code = system_cmd(process);
	free_data(false);
	exit (g_exit_code);
}

static void	single_cmd(t_process *process)
{
	char	*cmd;
	int		status;
	int		pid;

	status = 0;
	cmd = process->builtin;
	if (cmd && (!ft_strncmp(cmd, "exit", 5) || !ft_strncmp(cmd, "cd", 3)
		|| !ft_strncmp(cmd, "export", 7) || !ft_strncmp(cmd, "unset", 6)))
	{
		g_exit_code = builtin(process);
		return ;
	}
	send_heredoc(process);
	pid = fork();
	if (pid < 0)
		ms_error(5);
	if (pid == 0)
		handle_cmd(process);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_code = WEXITSTATUS(status);
}

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

void execute(void)
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
