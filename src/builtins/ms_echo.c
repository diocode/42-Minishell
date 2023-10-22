/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaiva-l <rpaiva-l@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:04:51 by rpaiva-l          #+#    #+#             */
/*   Updated: 2023/08/02 12:56:38 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

static void	ft_print(char **str, int i)
{
	while (str[i])
	{
		ft_putstr_fd(str[i], STDOUT_FILENO);
		i++;
		if (str[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
}

int	ms_echo(t_simple_cmds *process)
{
	float	flg;
	char	**cmd;
	int		i;
	int		j;

	cmd = process->str;
	flg = false;
	i = 1;
	while (cmd[i] && cmd[i][0] == '-' && cmd[i][1] == 'n')
	{
		j = 1;
		while (cmd[i][j] == 'n')
			j++;
		if (cmd[i][j] == '\0')
			flg = true;
		else
			break ;
		i++;
	}
	ft_print(cmd, i);
	if (flg == false)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
