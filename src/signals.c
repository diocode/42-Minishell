/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:46:45 by digoncal          #+#    #+#             */
/*   Updated: 2023/05/31 16:13:26 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_status;

void	handle_sign(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 130;
		ft_putchar_fd('\n', 1);
		ft_putstr_fd("minishell$ ", 1);
	}
	else if (sig == SIGQUIT)
	{
		g_status = 131;
		ft_putchar_fd('\n', 1);
		ft_putstr_fd("Quit\n", 1);
		ft_putstr_fd("minishell$ ", 1);
	}
}
