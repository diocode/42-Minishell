/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:59:14 by digoncal          #+#    #+#             */
/*   Updated: 2023/10/31 19:25:21 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_status;

static void	end_program(char *input, t_prompt	*prompt)
{
	free(input);
	free_data(prompt);
	rl_clear_history();
	exit(g_status);
}

static void	start_program(int ac)
{
	if (ac > 1)
	{
		printf("No arguments are accepted\n");
		exit(0);
	}
}

int	main(int ac, char **av, char **ev)
{
	t_prompt	*prompt;
	char		*input;

	start_program(ac);
	prompt = init_prompt(av, ev);
	while (prompt)
	{
		set_sign();
		input = readline("\001\e[1;32m\002minishell$ \001\e[0m\002");
		if (input == NULL)
		{
			free(input);
			ms_exit(prompt, NULL);
		}
		add_history(input);
		if (lexer(prompt, input) && prompt->lexer)
			parser(prompt);
		if (prompt->simple_cmds && !init_pid(prompt))
			execute(prompt);
		prompt = reset_prompt(prompt, av, ev);
	}
	end_program(input, prompt);
}
