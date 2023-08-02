/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaiva-l <rpaiva-l@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:21:54 by rpaiva-l          #+#    #+#             */
/*   Updated: 2023/07/24 11:59:32 by rpaiva-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*static int	text(char **av, char flag)
{
	int	x;
	int	y;

	x = 1;
	while (av[x])
	{
		y = 1;
		while (av[x][0] == '-' && av[x][y] == flag)
			y++;
		if (av[x][0] != '-' || av[x][y])
			break ;
		x++;
	}
	return (x);
}*/

void	ms_echo(t_prompt *prompt)
{
/*	int	x;

	x = text(av, 'n');
	if (x > 1)
	{
		while (av[x])
		{
			if (av[x][ft_strlen(av[x]) - 1] == '\n')
				break ;
			if (av[x + 1])
				printf("%s ", av[x++]);
			else
				printf("%s", av[x++]);
		}
	}
	else if (av[x])
	{
		while (av[x + 1])
			printf("%s ", av[x++]);
		printf("%s\n", av[x]);
	}
	else
		printf("\n");
*/
	(void)prompt;
}
