/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 23:22:17 by digoncal          #+#    #+#             */
/*   Updated: 2024/01/27 23:22:17 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_code;

static int	create_heredoc(t_token *redir, char *hd_file)
{
	int		fd;
	char	*input;

	fd = open(hd_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	input = readline("> ");
	while (input && ft_strncmp(redir->content, input,
			ft_strlen(redir->content) + 1) && g_exit_code != 2)
	{
		if (input[0])
			input = expand_heredoc(input);
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
		input = readline("> ");
	}
	free(input);
	if (g_exit_code == 2)
		return (1);
	close(fd);
	return (0);
}

static int	setup_heredoc(t_process *process, t_token *redirct, char *hd_file)
{
	int		flg;

	flg = create_heredoc(redirct, hd_file);
	if (process && process->builtin && ft_strncmp(process->builtin, "echo", 5))
		ms()->heredoc = true;
	return (flg);
}

static char	*gen_hd_filename(void)
{
	static int	i = 0;
	char		*num;
	char		*file_name;

	num = ft_itoa(i++);
	file_name = ft_strjoin(".tmp_file", num);
	free(num);
	return (file_name);
}

int	send_heredoc(t_process *process)
{
	t_token	*redir;

	redir = process->redirect;
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			if (process->hd_file)
				free(process->hd_file);
			process->hd_file = gen_hd_filename();
			if (setup_heredoc(process, redir, process->hd_file))
				return (1);
		}
		redir = redir->next;
	}
	return (0);
}
