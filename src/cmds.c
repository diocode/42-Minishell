/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:55:51 by digoncal          #+#    #+#             */
/*   Updated: 2023/09/10 16:55:51 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

static char	**get_paths(t_prompt *prompt)
{
	char	*path;
	char	*tmp;
	char	**paths;
	int		i;

	path = ms_getenv("PATH", prompt->env);
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

static int	system_cmd(t_prompt *prompt, t_simple_cmds *process)
{
	char	*path;
	char	**paths;
	int		i;

	if (!access(process->str[0], F_OK))
		execve(process->str[0], process->str, prompt->env);
	paths = get_paths(prompt);
	i = -1;
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], process->str[0]);
		if (!access(path, F_OK))
			execve(path, process->str, prompt->env);
		free(path);
	}
	free_array(paths);
	return (error_cmd_not_found(prompt));
}

static int	builtin(t_prompt *prompt, t_simple_cmds *process)
{
	char	*cmd;

	cmd = process->builtin;
	if (!ft_strncmp(cmd, "exit", 4))
		exit_env(prompt);
	else if (!ft_strncmp(cmd, "cd", 2))
		ms_cd(prompt, process);
	else if (!ft_strncmp(cmd, "export", 6))
		printf("\033[0;32mEXPORT STILL LOADING\033[0m\n");
	else if (!ft_strncmp(cmd, "unset", 5))
		printf("\033[0;32mUNSET STILL LOADING\033[0m\n");
	else if (!ft_strncmp(process->builtin, "echo", 4))
		printf("\033[0;32mECHO STILL LOADING\033[0m\n");
	else if (!ft_strncmp(process->builtin, "env", 3))
		ms_env(prompt);
	else if (!ft_strncmp(process->builtin, "pwd", 3))
		ft_printf("%s\n", ms_getenv("PWD", prompt->env));
	else
		return (1);
	return (0);
}

int	handle_cmd(t_prompt *prompt, t_simple_cmds *process)
{
	int	status;

	status = 0;
	if (process->redirct)
		if (setup_redirct(process))
			exit(1);
	if (process->builtin)
	{
		status = builtin(prompt, process);
		prompt->heredoc->error_num += status;
		exit(status);
	}
	if (process->str[0][0])
		return (system_cmd(prompt, process));
	return (0);
}

//Handle single cmds that cannot be run in a child process
int	single_cmd(t_prompt *prompt, t_simple_cmds *process)
{
	char	*cmd;
	int		status;
	int		pid;

	status = 0;
	prompt->simple_cmds = single_cmd_heredoc(prompt, process);
	cmd = process->builtin;
	if (cmd && (!ft_strncmp(cmd, "exit", 4) || !ft_strncmp(cmd, "cd", 2)
			|| !ft_strncmp(cmd, "export", 6) || !ft_strncmp(cmd, "unset", 5)))
	{
		prompt->heredoc->error_num += builtin(prompt, prompt->simple_cmds);
		return (0);
	}
	send_heredoc(prompt, prompt->simple_cmds);
	pid = fork();
	if (pid < 0)
		ms_error(5);
	if (pid == 0)
		handle_cmd(prompt, prompt->simple_cmds);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		prompt->heredoc->error_num += WEXITSTATUS(status);
	return (0);
}
