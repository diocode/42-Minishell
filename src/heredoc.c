/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:54:35 by digoncal          #+#    #+#             */
/*   Updated: 2023/09/06 12:52:14 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

int	init_heredoc(t_prompt *prompt)
{
	prompt->heredoc = malloc(sizeof(t_heredoc));
	if (!prompt->heredoc)
		return (ms_error(1));
	prompt->heredoc->error_num = 0;
	prompt->heredoc->status = false;
	return (0);
}

static int	create_heredoc(t_prompt *prompt, t_lexer *redirct,
	bool quotes, char *hd_file)
{
	int		fd;
	char	*input;

	fd = open(hd_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	input = readline("> ");
	while (input && ft_strncmp(redirct->str, input, ft_strlen(redirct->str))
		&& g_status != 2)
	{
		if (quotes == false)
			input = str_expander(prompt, input);
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
		input = readline("> ");
	}
	free(input);
	if (g_status == 2)
		return (1);
	close(fd);
	return (0);
}

static int	setup_heredoc(t_prompt *p, t_lexer *redirct, char *hd_file)
{
	bool	quotes;
	int		flg;

	if ((redirct->str[0] == '\"'
			&& redirct->str[ft_strlen(redirct->str) - 1] == '\"')
		|| (redirct->str[0] == '\''
			&& redirct->str[ft_strlen(redirct->str) - 1] == '\''))
		quotes = true;
	else
		quotes = false;
	delquotes(redirct->str, '\"');
	delquotes(redirct->str, '\'');
	flg = create_heredoc(p, redirct, quotes, hd_file);
	return (p->heredoc->status = true, flg);
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

int	send_heredoc(t_prompt *prompt, t_simple_cmds *process)
{
	t_lexer	*redirct;

	redirct = process->redirct;
	while (redirct)
	{
		if (!ft_strncmp(redirct->token, "<<", 3))
		{
			if (process->hd_file)
				free(process->hd_file);
			process->hd_file = gen_hd_filename();
			if (setup_heredoc(prompt, redirct, process->hd_file))
			{
				prompt->heredoc->error_num = 1;
				return (1);
			}
		}
		redirct = redirct->next;
	}
	return (0);
}
