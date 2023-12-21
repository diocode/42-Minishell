/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lists.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:57:08 by digoncal          #+#    #+#             */
/*   Updated: 2023/07/12 17:53:33 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer	*ms_lstlast(t_lexer *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ms_lstadd(t_lexer *lst, t_lexer *new)
{
	t_lexer	*tmp;

	if (!new)
		return ;
	if (!lst)
		lst = new;
	else
	{
		tmp = ms_lstlast(lst);
		tmp->next = new;
		new->prev = tmp;
	}
}

t_lexer	*ms_lstnew(char *content, char type)
{
	t_lexer	*node;

	if (!content)
		return (NULL);
	node = (t_lexer *) malloc(sizeof(t_lexer));
	if (!node)
		return (NULL);
	if (type == 'w')
	{
		node->str = ft_strdup(content);
		node->token = NULL;
	}
	else if (type == 't')
	{
		node->str = NULL;
		node->token = ft_strdup(content);
	}
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
