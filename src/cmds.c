/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 01:32:00 by digoncal          #+#    #+#             */
/*   Updated: 2024/01/30 01:32:00 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_code;

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

int	system_cmd(t_process *process)
{
	struct stat	st;
	char		*path;
	char		**paths;
	char		**env;
	int			i;

	if (!stat(process->args[0], &st) && S_ISDIR(st.st_mode))
		return (error_cmd_not_found(process));
	if (!access(process->args[0], F_OK))
	{
		env = list_to_array(ms()->env);
		execve(process->args[0], process->args, env);
		free_array(env);
		return (127);
	}
	paths = get_paths();
	if (!paths)
		return (error_cmd_not_found(process));
	i = -1;
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], process->args[0]);
		if (!access(path, F_OK))
		{
			env = list_to_array(ms()->env);
			execve(path, process->args, env);
			free_array(env);
			return (127);
		}
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

void	single_cmd(t_process *process)
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
