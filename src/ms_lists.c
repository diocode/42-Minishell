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
	if (type == 't')
	{
		node->str = NULL;
		node->token = ft_strdup(content);
	}
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	del_nodes(t_prompt *prompt, t_lexer *lexer)
{
	t_lexer	*last;

	if (!lexer || !lexer->next)
		return ;
	last = ms_lstlast(lexer);
	if (last && last->prev)
	{
		last->prev->next = NULL;
		if (last->str)
			free(last->str);
		if (last->token)
			free(last->token);
		free(last);
	}
	last = ms_lstlast(lexer);
	if (last && last->prev)
	{
		last->prev->next = NULL;
		if (last->str)
			free(last->str);
		if (last->token)
			free(last->token);
		free(last);
	}
	else
	{
		if (last->str)
			free(last->str);
		if (last->token)
			free(last->token);
		free(lexer);
		prompt->lexer = NULL;
	}
}

/*Merge last node with previous*/
void	merge_nodes(t_prompt *prompt)
{
	t_lexer	*last_node;
	char	*str;
	char	*token;

	str = NULL;
	token = NULL;
	last_node = ms_lstlast(prompt->lexer);
	if (last_node->prev && last_node->prev->str)
		str = ft_strdup(last_node->prev->str);
	else if (last_node->prev && last_node->prev->token)
		token = ft_strdup(last_node->prev->token);
	if (last_node->str)
		str = ft_strjoin(str, last_node->str);
	else if (last_node->token)
		token = ft_strjoin(token, last_node->token);
	del_nodes(prompt, prompt->lexer);
	if (str)
	{
		if (!prompt->lexer)
			prompt->lexer = ms_lstnew(str, 'w');
		else
			ms_lstadd(prompt->lexer, ms_lstnew(str, 'w'));
	}
	else if (token)
	{
		if (!prompt->lexer)
			prompt->lexer = ms_lstnew(token, 'w');
		else
			ms_lstadd(prompt->lexer, ms_lstnew(token, 'w'));
	}
	if (str)
		free(str);
	else if (token)
		free(token);
}
