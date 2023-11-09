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

static void	print_exit_status(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	while (str[i] && str[i] != '$')
		write(STDOUT_FILENO, &str[i++], 1);
	tmp = ft_itoa(g_status);
	ft_putstr_fd(tmp, STDOUT_FILENO);
	free(tmp);
	i += 2;
	while (str[i])
		write(STDOUT_FILENO, &str[i++], 1);
}

static void	ft_print(t_prompt *prompt, char **str, int i)
{
	while (str[i])
	{
		if (is_exit_status(str[i]))
		{
			if (prompt->exit_codes[current_exit_status(prompt)] == 1)
				print_exit_status(str[i]);
			else
				ft_putstr_fd(str[i], STDOUT_FILENO);
			prompt->exit_codes[current_exit_status(prompt)] = 2;
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
	ft_print(prompt, cmd, i);
	if (flg == false)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
