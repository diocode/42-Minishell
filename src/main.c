/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:59:14 by digoncal          #+#    #+#             */
/*   Updated: 2023/05/29 16:57:24 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ms_loop(t_info *info)
{
	char	*tmp;

	info->args = readline("minishell$ ");
	tmp = ft_strtrim(info->args, " ");
	free(info->args);
	info->args = tmp;
	if (!info->args)
		return (1);
	if (!info->args[0])
		reset_env(info);
	return (0);
}

t_info	*init_info(char **ev)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info->env = dup_arr(ev);
	find_pwd(info);
	info->args = NULL;
	setup_env(info);
	return (info);
}

int	main(int ac, char **av, char **ev)
{
	t_info	*info;

	if (ac > 1 || av[1])
	{
		printf("No arguments are accepted\n");
		exit(0);
	}
	info = init_info(ev);
	if (!info)
	{
		free_info(info);
		return (0);
	}
	ms_loop(info);
	/*while (1)
	{
		// Display prompt and read user input

		// Parse user input

		// Execute command

		// Cleanup and error handling
	}*/
	free_info(info);
	return (0);
}
