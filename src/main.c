/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:59:14 by digoncal          #+#    #+#             */
/*   Updated: 2023/07/22 18:49:28 by logname          ###   ########.fr       */
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
		input = readline("minishell$ ");
		if (input == NULL)
			exit_env(prompt);
		if (lexer(prompt, input) && prompt->lexer)
			parser(prompt);
		if (prompt->simple_cmds)
			execute(prompt);
		prompt = reset_prompt(prompt, av, ev);
	}
	free_data(prompt);
	free(input);
	exit(g_status);
}
