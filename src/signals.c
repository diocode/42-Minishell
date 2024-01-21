/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:05:02 by digoncal          #+#    #+#             */
/*   Updated: 2024/01/18 16:05:02 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_code;

static void	execute_sig(int sig)
{
	if (ms() && ms()->interact)
	{
		if (sig == SIGINT)
		{
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		if (sig == SIGQUIT)
		{
			printf("\033[K");
			rl_on_new_line();
			rl_redisplay();
		}
	}
	if (!(ms()->interact))
		if (sig == SIGINT)
			write(1, &"\n", 1);
	if (sig == SIGINT)
		g_exit_code = 130;
}

static void	handle(int sig)
{
	execute_sig(sig);
}

static void	init_sign(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	set_signals(void)
{
	init_sign();
	execute_sig(0);
}
