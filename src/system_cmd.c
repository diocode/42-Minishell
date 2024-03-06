/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:22:48 by digoncal          #+#    #+#             */
/*   Updated: 2024/03/06 13:22:48 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	exec_direct_path(t_process *process)
{
	struct stat	st;
	char		**env;

	if (!stat(process->args[0], &st)
		&& (S_ISDIR(st.st_mode) || S_ISREG(st.st_mode)))
		return (error_cmd_not_found(process));
	if (!access(process->args[0], F_OK))
	{
		env = list_to_array(ms()->env);
		execve(process->args[0], process->args, env);
		free_array(env);
		return (127);
	}
	return (0);
}

static int	search_and_exec_command(t_process *process)
{
	char	*path;
	char	**paths;
	char	**env;
	int		i;

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
			free(path);
			free_array(paths);
			return (127);
		}
		free(path);
	}
	free_array(paths);
	return (error_cmd_not_found(process));
}

int	system_cmd(t_process *process)
{
	int	result;

	result = exec_direct_path(process);
	if (result != 0)
		return (result);
	return (search_and_exec_command(process));
}
