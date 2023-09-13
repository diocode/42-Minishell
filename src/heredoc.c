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

static int	setup_heredoc(t_prompt *prompt, t_lexer *redirct, char *hd_file)
{
	bool	quotes;
	int		flg;

	flg = 0;
	if ((redirct->str[0] == '\"'
			&& redirct->str[ft_strlen(redirct->str) - 1] == '\"')
		|| (redirct->str[0] == '\''
			&& redirct->str[ft_strlen(redirct->str) - 1] == '\''))
		quotes = true;
	else
		quotes = false;
	delquotes(redirct->str, '\"');
	delquotes(redirct->str, '\'');
	prompt->heredoc->in_heredoc = 1;
	flg = create_heredoc(prompt, redirct, quotes, hd_file);
	prompt->heredoc->in_heredoc = 0;
	prompt->heredoc->status = true;
	return (flg);
}

static char	*gen_hd_filename(void)
{
	static int	i = 0;
	char		*num;
	char		*file_name;

	num = ft_itoa(i++);
	file_name = ft_strjoin("build/.tmp_heredoc_file_", num);
	free(num);
	return (file_name);
}

int	send_heredoc(t_prompt *prompt, t_simple_cmds *process)
{
	t_lexer	*redirct;

	redirct = process->redirct;
	while (redirct)
	{
		if (!ft_strncmp(redirct->token, "<<", 2))
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

t_simple_cmds	*single_cmd_heredoc(t_prompt *prompt, t_simple_cmds *p)
{
	t_lexer	*redirct;

	p->str = single_cmd_expander(prompt, p->str);
	redirct = p->redirct;
	while (p->redirct)
	{
		if (ft_strncmp(p->redirct->token, "<<", 2))
			p->redirct->str = str_expander(prompt, p->redirct->str);
		redirct = redirct->next;
	}
	p->redirct = redirct;
	return (p);
}
