/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:59:14 by digoncal          #+#    #+#             */
/*   Updated: 2023/05/31 16:05:33 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

static void	ms_getpid(t_prompt *prompt)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0 || !pid)
	{
		if (pid < 0)
			ms_error(FORKERR, 1, NULL);
		free_array(prompt->env);
		exit(1);
	}
	waitpid(pid, NULL, 0);
	prompt->pid = pid - 1;
}

static t_prompt	*init_vars(t_prompt *prompt, char **av, char *path)
{
	path = getcwd(NULL, 0);
	(void)av;
	(void)path;
	//DO: fully init prompt and variables
	return (prompt);
}

static t_prompt	*init_prompt(char **av, char **ev)
{
	t_prompt	*prompt;
	char		*path;

	prompt = malloc(sizeof(t_prompt));
	if (!prompt)
		return (NULL);
	g_status = 0;
	path = NULL;
	prompt->cmds = NULL;
	prompt->env = dup_arr(ev);
	ms_getpid(prompt);
	prompt = init_vars(prompt, av, path);
	return (prompt);
}

int	main(int ac, char **av, char **ev)
{
	t_prompt	*prompt;
	char		*input;

	if (ac > 1 || av[1])
	{
		printf("No arguments are accepted\n");
		exit(0);
	}
	prompt = init_prompt(av, ev);
	while (prompt)
	{
		signal(SIGINT, handle_sign);
		signal(SIGQUIT, handle_sign);
		input = readline("minishell$ ");
		if (check_prompt(prompt, input))
			break ;
	}
	free_data(prompt);
	exit(g_status);
}
