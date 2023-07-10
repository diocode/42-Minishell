/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:59:14 by digoncal          #+#    #+#             */
/*   Updated: 2023/07/10 16:04:30 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

static void	parser_tester(void)
{
	t_simple_cmds	*node;
	char			*str;
	char			*builtin;
	char			*redirct;
	char			*file;

	str = "echo -n HELLO > file.txt";
	builtin = "echo";
	redirct = ">";
	file = "file.txt";

	node = malloc(sizeof(t_simple_cmds));
	node->str = ft_split(str, ' ');
	node->builtin = ft_strdup(builtin);
	node->redirct = ms_lstnew(">", 't');
	node->num_redirct = 1;
	node->file = ft_strdup(file);
	node->next = NULL;
	node->prev = NULL;

	printf("-----------\nSTR: ");
	for (int i = 0; node->str[i]; i++)
		printf("[%s] ", node->str[i]);
	printf("\n");
	printf("BUILTIN: %s\n", node->builtin);
	printf("REDIRCT NUMBER: %d\n", node->num_redirct);
	printf("REDIRCT: %s\n", node->redirct->token);
	printf("FILE: %s\n-----------\n", node->file);
}

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
		parser_tester(); //DEV
	}
	free_data(prompt);
	exit(g_status);
}
