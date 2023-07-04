/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:59:14 by digoncal          #+#    #+#             */
/*   Updated: 2023/07/04 18:19:39 by digoncal         ###   ########.fr       */
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
			input = "exit";
		}
		lexer(prompt, input);
		//parser(prompt);
		/*//=========================== TESTING ===============================
		printf("LEXER: ");
		for (t_lexer *node = *prompt->lexer; node; node = node->next)
		{
			if (!node->str)
				printf("[%s] ", node->token);
			else
				printf("[%s] ", node->str);
		}
		printf("\n");
		//=========================== TESTING ===============================*/
		reset_lexer(prompt);
	}
	free_data(prompt);
	exit(g_status);
}
