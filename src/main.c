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

void	dev_mod(void)
{
	t_token	*tmp = NULL;
	printf("\033[32;1m=========== DEV MOD ==========\033[0m\n");
	if (ms()->input)
	{
		printf("\n\033[32;1mINPUT: \033[0m");
		printf("%s\n", ms()->input);
	}
	if (ms()->lexer)
	{
		 while (ms()->lexer->prev)
			ms()->lexer = ms()->lexer->prev;
		printf("\n\033[32;1mLEXER: \033[0m");
		tmp = ms()->lexer;
		while(tmp)
		{
			printf("[%s] ", tmp->content);
			tmp = tmp->next;
		}
		printf("\n");
		printf("\033[32;1m==============================\033[0m\n");
	}
}

/* ============================  dev mod ============================ */

t_shell	*ms(void)
{
	static t_shell	ms;

	return (&ms);
}

static void ms_loop(void)
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
				parser();
			dev_mod();
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
