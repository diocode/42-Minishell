/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redircts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:42:09 by digoncal          #+#    #+#             */
/*   Updated: 2023/09/10 19:42:09 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_outfile(t_lexer	*redirct)
{
	int	fd;

	if (!ft_strncmp(redirct->token, ">>", 3))
		fd = open(redirct->str, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(redirct->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (ms_error(6));
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (ms_error(4));
	close(fd);
	return (0);
}

static int	ft_infile(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ms_error(7));
	if (dup2(fd, STDIN_FILENO) < 0)
		return (ms_error(4));
	close(fd);
	return (0);
}

int	setup_redirct(t_simple_cmds *process)
{
	t_lexer	*redirct;

	redirct = process->redirct;
	while (redirct)
	{
		if (!ft_strncmp(redirct->token, "<", 2))
		{
			if (ft_infile(redirct->str))
				return (1);
		}
		else if (!ft_strncmp(redirct->token, "<<", 3))
		{
			if (ft_infile(process->hd_file))
				return (1);
		}
		else if (!ft_strncmp(redirct->token, ">", 2)
			|| !ft_strncmp(redirct->token, ">>", 3))
			if (ft_outfile(redirct))
				return (1);
		redirct = redirct->next;
	}
	return (0);
}
