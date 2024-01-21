/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:24:00 by digoncal          #+#    #+#             */
/*   Updated: 2024/01/18 13:24:00 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	free_token(t_token *lst)
{
	t_token	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		if (lst->content)
			free(lst->content);
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

static void	free_env(void)
{
	t_env	*tmp;
	t_env	*next;

	tmp = ms()->env;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = next;
	}
}

void	free_data(bool reset)
{
	if (!ms())
		return ;
	if (ms()->input)
		free(ms()->input);
	if (ms()->lexer)
		free_token(ms()->lexer);
	if (reset)
	{
		ms()->input = NULL;
		ms()->lexer = NULL;
		ms()->process = NULL;
		ms()->pid = 0;
		ms()->interact = false;
		ms()->quote[0] = false;
		ms()->quote[1] = false;
	}
	else if (ms()->env)
		free_env();
}
