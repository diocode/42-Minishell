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

	printf("\n====================== TESTING (PID: %d) ==========================\n", prompt->pid);
	printf("\n* ENVIRONMENT *");
	printf("\n--------------------------------------\n\n");
	i = -1;
	while (prompt->env[++i])
		printf("[%d] %s\n", i, prompt->env[i]);
	printf("\n\nINPUT: %s\n\nLEXER: ", input);
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
	int				j;
	int				i;

	printf("\n\n\n* PARSER *");
	printf("\n--------------------------------------\n");
	cmds = prompt->simple_cmds;
	j = 0;
	while (cmds)
	{
		printf("\nPROCESS[%d]:\n", ++j);
		printf("\n  STR: ");
		i = -1;
		while (cmds->str && cmds->str[++i])
			printf("[%s] ", cmds->str[i]);
		printf("\n  BUILTIN: %s\n", cmds->builtin);
		printf("  REDIRCT NUMBER: %d\n", cmds->num_redirct);
		printf("  REDIRCT: %s\n", cmds->redirct);
		printf("  FILE: %s\n\n", cmds->file);
		cmds = cmds->next;
	}
	printf("\n====================== TESTING (PID: %d) ==========================\n\n", prompt->pid);
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
		{
			g_status = 6;
			free(input);
			printf("exit\n");
			free_data(prompt);
			exit(g_status);
		}
		dev_mod0(prompt, input);
		lexer(prompt, input);
		dev_mod1(prompt);
		if (prompt->lexer)
		{
			parser(prompt);
			if (prompt->simple_cmds)
				dev_mod2(prompt);
		}
		prompt = reset_prompt(prompt, av, ev);
	}
	free_data(prompt);
	free(input);
	exit(g_status);
}

/*

 = TEST =
 	-> echo "testy test" >> note.txt -l | cat "Diogo Silva" env -n >> t1 | 'work"please' pwd cd ok? < file.file

 = BUGS =
 	->

*/