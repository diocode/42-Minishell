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

static int expander(void)
{
	t_token		*tmp;

	tmp = ms()->lexer;
	while (tmp)
	{
		if (!valid_quotes(tmp->content))
			return (1);
		if (!valid_dollar(tmp->content)) // checks for $ and if its expandable (single quotes and <<)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	parser(void)
{
	if (expander())
		return ;
}
