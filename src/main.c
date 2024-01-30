/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:42:09 by digoncal          #+#    #+#             */
/*   Updated: 2024/01/18 11:42:09 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_code;

t_shell	*ms(void)
{
	static t_shell	ms;

	return (&ms);
}

static void	ms_loop(void)
{
	while (true)
	{
		ms()->interact = true;
		ms()->input = readline("\001\e[35;1m\002minishell$ \001\e[0m\002");
		ms()->interact = false;
		if (ms()->input == NULL)
		{
			free(ms()->input);
			ft_putendl_fd("exit", STDOUT_FILENO);
			ms_exit(ms()->process);
		}
		if (ms()->input[0])
		{
			add_history(ms()->input);
			lexer(ms()->input);
			if (ms()->lexer)
				if (!parser() && !init_pid())
					execute();
		}
		free_data(true);
	}
}

int	main(int ac, char **av, char **ev)
{
	if (ac > 1)
	{
		printf("No arguments are accepted\n");
		exit(0);
	}
	init(av, ev);
	set_signals();
	ms_loop();
}
