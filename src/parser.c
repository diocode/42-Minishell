/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 20:47:13 by digoncal          #+#    #+#             */
/*   Updated: 2024/01/21 20:47:13 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*static int check_errors(void)
{
	t_token		*tmp;

	tmp = ms()->lexer;
	while (tmp)
	{
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT
			|| tmp->type == REDIR2_OUT)
		{
			if ()
		}
		tmp = tmp->next;
	}
	return (0);
}*/

/*static t_token *get_curr_process(int pipes)
{
	t_token		*tmp;

	tmp = ms()->lexer;
	while (tmp)
	{
		if (tmp ->)
		tmp = tmp->next;
	}
	return (ms()->lexer);
}

static int	generate_process(int pipes)
{
	t_token		*tmp;

	tmp = get_curr_process(pipes);
	return (0);
}*/

void	parser(void)
{
	int			pipes;

	expander();
	pipes = count_pipes(ms()->lexer);
	while (pipes >= 0)
	{
		/*if (generate_process(pipes))
			break ;*/
		pipes--;
	}
}
