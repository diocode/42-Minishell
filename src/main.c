/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:59:14 by digoncal          #+#    #+#             */
/*   Updated: 2023/10/16 13:32:21 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

int	main(int ac, char **av, char **ev)
{
	t_prompt	*prompt;
	char		*input;

	if (ac > 1)
	{
		printf("No arguments are accepted\n");
		exit(0);
	}
	prompt = init_prompt(av, ev);
	while (prompt)
	{
		set_sign();
		input = readline("\033[0;32mminishell$ \033[0m");
		if (input == NULL || !ft_strncmp(input, "exit", 4)) //exit cmp might be unnecesary after pipe fix
			exit_env(prompt);
		else
			add_history(input);
		if (lexer(prompt, input) && prompt->lexer)
			parser(prompt);
		if (input[0] && prompt->simple_cmds && !init_pid(prompt))
			execute(prompt);
		prompt = reset_prompt(prompt, av, ev);
	}
	free(input);
	free_data(prompt);
	exit(g_status);
}
