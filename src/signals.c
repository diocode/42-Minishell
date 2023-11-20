/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:46:45 by digoncal          #+#    #+#             */
/*   Updated: 2023/09/13 14:20:16 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

void	execute_sig(int sig, void *prompt)
{
	static t_prompt	*static_prompt;

	if (!static_prompt && prompt)
		static_prompt = (t_prompt *)prompt;
	if (static_prompt && static_prompt->interact)
	{
		if (sig == SIGINT)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		if (sig == SIGQUIT)
		{
			printf("\b\b  \b\b");
			rl_redisplay();
		}
	}
	if (!(static_prompt->interact))
		if (sig == SIGINT)
			write(1, &"\n", 1);
	if (sig == SIGINT)
		g_status = 130;
}

static void	handle(int sig)
{
	execute_sig(sig, 0);
}

void	set_sign(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
