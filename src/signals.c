/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:46:45 by digoncal          #+#    #+#             */
/*   Updated: 2023/06/13 12:28:23 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_status;

void	handle_sign(int sig, siginfo_t *info, void *c)
{
	(void)info;
	(void)c;
	if (sig == SIGINT)
	{
		g_status = 2;
		printf("\b\b  \b\b");
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		g_status = 3;
		printf("\b\b  \b\b");
		rl_redisplay();
	}
}

void	set_sign(void)
{
	struct sigaction	sig;

	sig.sa_sigaction = &handle_sign;
	sig.sa_flags = 0;
	sigemptyset(&sig.sa_mask);
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
}
