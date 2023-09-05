/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:54:35 by digoncal          #+#    #+#             */
/*   Updated: 2023/09/05 15:54:35 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

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
	int		signal;

	tmp = process->redirct;
	signal = 0;
	while (process->redirct)
	{
		if (ft_strncmp(process->redirct->token, "<<", 2))
		{
			if (process->hd_file)
				free(process->hd_file);
			process->hd_file = gen_hd_filename();
			signal = /*CREATE HEREDOC*/;
			if (signal)
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
