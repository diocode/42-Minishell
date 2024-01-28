/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 12:08:46 by digoncal          #+#    #+#             */
/*   Updated: 2024/01/28 12:08:46 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_code;

static int	ft_outfile(t_token *redir)
{
	int	fd;

	if (redir->type == REDIR2_OUT)
		fd = open(redir->content, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(redir->content, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (ms_error(6), 1);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (ms_error(4), 1);
	close(fd);
	return (0);
}

static int	ft_infile(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ms_error(7), 1);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (ms_error(4), 1);
	close(fd);
	return (0);
}

int	setup_redirect(t_process *process)
{
	t_token	*redir;

	redir = process->redirect;
	while (redir)
	{
		if (redir->type == REDIR_IN)
		{
			if (ft_infile(redir->content))
				return (1);
		}
		else if (redir->type == HEREDOC)
		{
			if (ft_infile(process->hd_file))
				return (1);
		}
		else if (redir->type == REDIR_OUT || redir->type == REDIR2_OUT)
			if (ft_outfile(redir))
				return (1);
		redir = redir->next;
	}
	return (0);
}
