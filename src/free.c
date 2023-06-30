/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:29:47 by digoncal          #+#    #+#             */
/*   Updated: 2023/06/20 12:12:48 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

void	ms_exit(t_prompt *prompt)
{
	printf("exit\n");
	free_data(prompt);
	exit(g_status);
}

void	free_lexer(t_lexer **lst)
{
	t_lexer	*tmp;
	t_lexer	*node;

	node = (*lst);
	while (node)
	{
		tmp = node;
		node = node->next;
		free(tmp);
	}
	free(lst);
}

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
	if (prompt->lexer)
		free_lexer(prompt->lexer);
	if (prompt->env)
		free_array(prompt->env);
	free(prompt);
}
