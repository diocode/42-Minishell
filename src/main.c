/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:59:14 by digoncal          #+#    #+#             */
/*   Updated: 2023/07/12 15:03:48 by digoncal         ###   ########.fr       */
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
		{
			g_status = 6;
			free(input);
			printf("exit\n");
			free_data(prompt);
			exit(6);
		}
		lexer(prompt, input);
		if (prompt->lexer)
			parser(prompt); //BUGS: {"" INPUT} {multiple builtins}
		else if (prompt->simple_cmds)
			prompt = reset_prompt(prompt, av, ev);
	}
	free_data(prompt);
	exit(g_status);
}
