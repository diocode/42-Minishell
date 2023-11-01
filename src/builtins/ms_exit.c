/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 21:15:54 by digoncal          #+#    #+#             */
/*   Updated: 2023/10/22 22:56:07 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

static void	exit_code(char **str)
{
	int	exit_code;

	if (!str[1])
		exit_code = 0;
	else if (is_digit(str[1]))
		exit_code = ft_atoi(str[1]);
	else
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(str[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit_code = 2;
	}
	free_array(str);
	exit(exit_code);
}

int	ms_exit(t_prompt *prompt, t_simple_cmds *simple_cmd)
{
	char	**str;

	ft_putendl_fd("exit", STDERR_FILENO);
	if (!simple_cmd)
	{
		free_data(prompt);
		exit(0);
	}
	if (simple_cmd->str[1] && simple_cmd->str[2])
	{
		if (is_digit(simple_cmd->str[1]))
		{
			ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
			g_status = 127;
			return (g_status);
		}
	}
	str = dup_arr(simple_cmd->str);
	free_data(prompt);
	rl_clear_history();
	exit_code(str);
	return (EXIT_SUCCESS);
}
