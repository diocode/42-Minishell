/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 13:18:18 by digoncal          #+#    #+#             */
/*   Updated: 2023/07/28 13:18:18 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

static void	close_pipes(int **pipe_fd, int id)
{
	while (pipe_fd[id])
	{
		close(pipe_fd[id][0]);
		close(pipe_fd[id][1]);
	}
	id--;
}

static void	exe_pipes(t_prompt *prompt, int **pipe_fd)
{
	t_simple_cmds	*process;
	int				id;
	int				pid;

	id = 0;
	pipe_fd[id] = malloc(sizeof(int) * 2);
	pipe(pipe_fd[id]);
	pid = fork();
	if (pid == 0)
	{
		dup2(pipe_fd[id][1], STDOUT_FILENO);
		close_pipes(pipe_fd, id);
		handle_cmd(prompt, id);
		exit(0);
	}
	else
	{
		process = prompt->simple_cmds->next;
		while (process)
		{
			id++;
			if (process->next)
			{
				//...
			}
		}
	}
}

int	handle_pipes(t_prompt *prompt, int n_pipes)
{
	int	**pipe_fd;

	if (!prompt->simple_cmds)
		return (0);
	if (n_pipes)
	{
		pipe_fd = ft_calloc(n_pipes + 1, sizeof(int *));
		exe_pipes(prompt, pipe_fd);
	}
}
