/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.1337.ma>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:30:58 by dev               #+#    #+#             */
/*   Updated: 2023/07/23 12:26:47 by logname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

static void	dev_mod0(t_prompt *prompt, char *input)
{
	int				i;

	printf("\n\033[1;32m====================== TESTING ==========================\033[0m\n");
	printf("\n\033[1;32m* ENVIRONMENT *\033[0m");
	printf("\n\033[1;32m--------------------------------------\033[0m\n\n");
	i = -1;
	while (prompt->env[++i])
		printf("\033[0;34m[%d]\033[0m %s\n", i, prompt->env[i]);
	printf("\n\n\033[1;32mINPUT:\033[0m %s\n\n\033[1;32mLEXER:\033[0m ", input);
}

static void	dev_mod1(t_prompt *prompt)
{
	for (t_lexer *node = prompt->lexer; node; node = node->next)
	{
		if (!node->str)
			printf("[%s] ", node->token);
		else
			printf("[%s] ", node->str);
	}
}

static void	dev_mod2(t_prompt *prompt)
{
	t_simple_cmds	*cmds;
	t_lexer			*node;
	int				j;
	int				i;

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
		cmds = cmds->next;
	}
}

static void	dev_mod3(t_prompt *prompt)
{
	t_simple_cmds	*cmds;
	t_lexer			*node;
	int				j;
	int				i;

	printf("\n\n\n\033[1;32m* EDITED PARSER *\033[0m");
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
		cmds = cmds->next;
	}
	printf("\n\033[1;32m====================== TESTING ==========================\033[0m\n\n");
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
		input = readline("minishell@dev$ ");
		if (input == NULL)
			exit_env(prompt);
		dev_mod0(prompt, input);
		lexer(prompt, input);
		dev_mod1(prompt);
		if (prompt->lexer)
		{
			parser(prompt);
			if (prompt->simple_cmds)
			{
				dev_mod2(prompt);
				execute(prompt);
				dev_mod3(prompt);
			}
		}
		prompt = reset_prompt(prompt, av, ev);
	}
	free_data(prompt);
	free(input);
	exit(g_status);
}

/*

 = TEST =
 	echo "'test'" >> note.txt -l | cat $USER echo -n << t1 > lol | pwd 'workpls' cd ok? < test.txt

 = BUGS =

 = NOTES =
 	-> run valgrind without readline leaks:
 	   valgrind -s --suppressions=readline_leaks.txt --leak-check=full --show-leak-kinds=all ./minishell

*/