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
/*
int	dev_mod(void)
{
	printf("\033[32;1m=========== DEV MOD ==========\033[0m\n");
	if (ms()->lexer)
	{
		t_token	*lexer = NULL;
		printf("\n\033[32;1mLEXER: \033[0m");
		lexer = ms()->lexer;
		while(lexer)
		{
			printf("[%s] ", lexer->content);
			lexer = lexer->next;
		}
	}
	t_process	*process = ms()->process;
	int n = 1;
	while (process)
	{
		printf("\n\n\033[32;1mPROCESS (%d): \033[0m", n++);
		printf("\n");
		printf("\033[34m   ARGS: \033[0m");
		if (process->args)
		{
			if (!process->args[0])
			{
				printf("[");
				printf("\033[90m(null)\033[0m");
				printf("]");
			}
			else
			{
				for (int i = 0; process->args[i]; i++)
					printf("[%s] ", process->args[i]);
			}

		}
		else
			printf("\033[90m(null)\033[0m");
		printf("\n\033[34m   BUILTIN: \033[0m");
		if (process->builtin)
			printf("[%s]\n", process->builtin);
		else
			printf("\033[90m(null)\033[0m\n");
		printf("\033[34m   REDIRECT: \033[0m");
		t_token	*redir = process->redirect;
		if (!redir)
			printf("\033[90m(null)\033[0m");
		else
		{
			while (redir)
			{
				if (redir->type == REDIR_IN)
					printf("[<] ");
				if (redir->type == REDIR_OUT)
					printf("[>] ");
				if (redir->type == REDIR2_OUT)
					printf("[>>] ");
				if (redir->type == HEREDOC)
					printf("[<<] ");
				printf("[%s]  ", redir->content);
				redir = redir->next;
			}
		}
		printf("\n\033[34m   HD_FILE: \033[0m");
		if (process->hd_file)
			printf("%s", process->hd_file);
		else
			printf("\033[90m(null)\033[0m");
		process = process->next;
	}
	printf("\n\n");
	printf("\033[32;1m==============================\033[0m\n");
	return (1);
}*/

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
				if (!parser() && !init_execute())
				{
					//dev_mod();
					execute();
				}
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
