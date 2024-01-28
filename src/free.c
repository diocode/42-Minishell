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

static void	free_process(void)
{
	t_process	*tmp;

	while (ms()->process)
	{
		if (ms()->process->args)
			free_array(ms()->process->args);
		if (ms()->process->redirect)
		{
			while (ms()->process->redirect->prev)
				ms()->process->redirect = ms()->process->redirect->prev;
			free_token(ms()->process->redirect);
		}
		if (ms()->process->builtin)
			free(ms()->process->builtin);
		if (ms()->process->hd_file)
			free(ms()->process->hd_file);
		tmp = ms()->process;
		ms()->process = ms()->process->next;
		free(tmp);
	}
}

void	free_env(t_env *tmp)
{
	t_env	*next;

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
	if (ms()->tmp_env)
		free_array(ms()->tmp_env);
	if (ms()->lexer)
		free_token(ms()->lexer);
	if (ms()->process)
		free_process();
	if (ms()->pid)
		free(ms()->pid);
	if (reset)
	{
		ms()->input = NULL;
		ms()->tmp_env = NULL;
		ms()->lexer = NULL;
		ms()->process = NULL;
		ms()->pid = NULL;
		ms()->interact = false;
		ms()->heredoc = false;
		ms()->reset = true;
		ms()->quote[0] = false;
		ms()->quote[1] = false;
	}
	else if (ms()->env)
		free_env(ms()->env);
}
