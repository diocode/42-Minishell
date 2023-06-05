/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:02:19 by digoncal          #+#    #+#             */
/*   Updated: 2023/05/31 15:11:54 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_prompt(t_prompt *prompt, char *input)
{
	if (!input)
	{
		printf("exit\n");
		return (1);
	}
	if (input[0] != '\0')
		add_history(input);
	(void)prompt;
	//DO: create array with all the cmds from input divided
	//DO: set enviornment??
	return (0);
}
