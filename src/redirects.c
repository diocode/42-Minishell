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

static int	file_error(char *str)
{
	struct stat	st;
	char		*tmp;

	tmp = ": No such file or directory";
	if ((str[0] == '/' || str[0] == '.'))
	{
		if (stat(str, &st) == 0)
		{
			if (S_ISDIR(st.st_mode))
				tmp = ": Is a directory";
			else if (S_IXUSR)
				tmp = ": Permission denied";
		}
	}
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(tmp, STDERR_FILENO);
	return (1);
}

static int	ft_outfile(t_token *redir)
{
	int	fd;

	if (redir->type == REDIR2_OUT)
		fd = open(redir->content, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(redir->content, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (file_error(redir->content));
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
		return (file_error(file));
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
