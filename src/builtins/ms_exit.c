/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:19:18 by digoncal          #+#    #+#             */
/*   Updated: 2024/01/18 16:19:18 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_code;

static void	exit_code(char **code)
{
	int	exit_code;

	if (!code || !code[0])
		exit_code = 0;
	else if (is_digit(code[0]) || ft_atoi(code[0]))
		exit_code = ft_atoi(code[0]);
	else if (code[0][0] && code[0][0] == '-' && is_digit(code[0] + 1))
		exit_code = 256 - ft_atoi(code[0] + 1);
	else
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(code[0], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit_code = 2;
	}
	free_array(code);
	exit(exit_code);
}

int	ms_exit(t_process *process)
{
	char	**code;

	if (!process)
	{
		free_data(false);
		exit(g_exit_code);
	}
	if (!process->prev)
		ft_putendl_fd("exit", STDOUT_FILENO);
	if (process->args && process->args[0] && process->args[1])
	{
		if (is_digit(process->args[0]))
		{
			ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
			g_exit_code = 1;
			return (g_exit_code);
		}
	}
	code = dup_arr(process->args);
	free_data(false);
	rl_clear_history();
	exit_code(code);
	return (EXIT_SUCCESS);
}
