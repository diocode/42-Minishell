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

t_shell	*sh(void)
{
	static t_shell	ms;

	return (&ms);
}

int	main(int ac, char **av, char **ev)
{
	if (ac > 1)
	{
		printf("No arguments are accepted\n");
		exit(0);
	}
	(void)av;
	(void)ev;
}
