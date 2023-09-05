/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:54:35 by digoncal          #+#    #+#             */
/*   Updated: 2023/09/05 16:50:24 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

int	create_heredoc(t_prompt *prompt, t_lexer *redirct, char *hd_file)
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
	//IM HERE!!!!!!!!
	g_global.stop_redirct = 0;
	g_global.in_redirct = 1;
	flg = create_redirct(redirct, quotes, tools, file_name);
	g_global.in_redirct = 0;
	tools->redirct = true;
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
	t_lexer	*tmp;

	tmp = process->redirct;
	while (process->redirct)
	{
		if (ft_strncmp(process->redirct->token, "<<", 2))
		{
			if (process->hd_file)
				free(process->hd_file);
			process->hd_file = gen_hd_filename();
			if (create_heredoc(prompt, process->redirct, process->hd_file))
			{
				prompt->heredoc->error_num = 1;
				return (1);
			}
		}
		process->redirct = process->redirct->next;
	}
	process->redirct = tmp;
	return (0);
}
