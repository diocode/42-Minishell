/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 21:50:23 by digoncal          #+#    #+#             */
/*   Updated: 2024/01/27 21:50:23 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_print(char **str, int i)
{
	if (!str)
		return ;
	while (str[i])
	{
		ft_putstr_fd(str[i], STDOUT_FILENO);
		i++;
		if (str[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
}

int	ms_echo(t_process *process)
{
	float	flg;
	int		i;
	int		j;

	flg = false;
	i = 0;
	while (process->args && process->args[i] && process->args[i][0] == '-'
			&& process->args[i][1] == 'n')
	{
		j = 1;
		while (process->args[i][j] == 'n')
			j++;
		if (process->args[i][j] == '\0')
			flg = true;
		else
			break ;
		i++;
	}
	ft_print(process->args, i);
	if (flg == false)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
