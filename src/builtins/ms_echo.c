/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:04:51 by digoncal          #+#    #+#             */
/*   Updated: 2023/10/31 19:12:54 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

static void	ft_print(char **str, int i)
{
	char	*tmp;

	while (str[i])
	{
		if (!ft_strncmp(str[i], "$?", 2) && is_expandable(array_to_str(str)))
		{
			tmp = ft_itoa(g_status);
			ft_putstr_fd(tmp, STDOUT_FILENO);
			free(tmp);
		}
		else
			ft_putstr_fd(str[i], STDOUT_FILENO);
		i++;
		if (str[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
}

int	ms_echo(t_prompt *prompt, t_simple_cmds *process)
{
	float	flg;
	char	**cmd;
	int		i;
	int		j;

	(void)prompt;
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
