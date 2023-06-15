/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:29:47 by digoncal          #+#    #+#             */
/*   Updated: 2023/06/14 11:39:27 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_data(t_prompt *prompt)
{
	if (!prompt)
		return ;
	if (prompt->cmds)
		free(prompt->cmds);
	if (prompt->env)
		free_array(prompt->env);
	free(prompt);
}
