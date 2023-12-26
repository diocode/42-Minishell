/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:59:14 by digoncal          #+#    #+#             */
/*   Updated: 2023/12/19 15:57:00 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_status;

/*static void	dev_mod(t_prompt *prompt)
{
	t_simple_cmds	*cmds;
	t_lexer			*node;
	int				j;
	int				i;

	printf("\n\033[1;32m* LEXER *\033[0m");
	printf("\n\033[1;32m--------------------------------------\033[0m\n");
	for (t_lexer *node = prompt->lexer; node; node = node->next)
	{
		if (!node->str)
			printf("[%s] ", node->token);
		else
			printf("[%s] ", node->str);
	}
	printf("\n\n\n\033[1;32m* PARSER *\033[0m");
	printf("\n\033[1;32m--------------------------------------\033[0m\n");
	cmds = prompt->simple_cmds;
	j = 0;
	while (cmds)
	{
		printf("\nPROCESS[%d]:\n", ++j);
		printf("\n  \033[0;34mSTR:\033[0m ");
		i = -1;
		while (cmds->str && cmds->str[++i])
			printf("[%s] ", cmds->str[i]);
		printf("\n  \033[0;34mBUILTIN:\033[0m %s\n", cmds->builtin);
		printf("  \033[0;34mREDIRCT NUMBER:\033[0m %d\n", cmds->num_redirct);
		printf("  \033[0;34mREDIRCT:\033[0m ");
		node = cmds->redirct;
		while (node)
		{
			if (node->token)
				printf("[%s]", node->token);
			if (node->str)
				printf("[%s]", node->str);
			printf("  ");
			node = node->next;
		}
		printf("\n");
		cmds = cmds->next;
	}
	printf("\n\033[1;32m* OUTPUT *\033[0m");
	printf("\n\033[1;32m--------------------------------------\033[0m\n");
}*/

static char	*handle_input(t_prompt *prompt, char *input)
{
	if (input == NULL)
	{
		free(input);
		ms_exit(prompt, NULL);
	}
	add_history(input);
	if (input && input[0])
		input = expand_input(prompt, input);
	return (input);
}

static t_prompt	*start_program(int ac, char **av, char **ev)
{
	t_prompt	*prompt;

	if (ac > 1)
	{
		printf("No arguments are accepted\n");
		exit(0);
	}
	prompt = init_prompt(av, ev);
	set_sign();
	execute_sig(0, prompt);
	return (prompt);
}

int	main(int ac, char **av, char **ev)
{
	t_prompt	*prompt;
	char		*input;

	prompt = start_program(ac, av, ev);
	while (prompt)
	{
		prompt->interact = true;
		input = readline("\001\e[1;32m\002minishell$ \001\e[0m\002");
		prompt->interact = false;
		input = handle_input(prompt, input);
		if (input && !lexer(prompt, input))
			if (!parser(prompt))
				if (!init_pid(prompt) && !init_heredoc(prompt))
					execute(prompt);
		reset_prompt(prompt, av, ev);
	}
}
