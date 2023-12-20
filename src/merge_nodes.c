/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:46:41 by digoncal          #+#    #+#             */
/*   Updated: 2023/12/20 13:46:41 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_last_node(t_lexer *last)
{
	if (last->str)
		free(last->str);
	if (last->token)
		free(last->token);
	free(last);
}

static void	del_nodes(t_prompt *prompt, t_lexer *lexer)
{
	t_lexer	*last;

	if (!lexer || !lexer->next)
		return ;
	last = ms_lstlast(lexer);
	if (last && last->prev)
	{
		last->prev->next = NULL;
		free_last_node(last);
	}
	last = ms_lstlast(lexer);
	if (last && last->prev)
	{
		last->prev->next = NULL;
		free_last_node(last);
	}
	else
	{
		free_last_node(last);
		free(lexer);
		prompt->lexer = NULL;
	}
}

static char	*merge_str_tokens(t_lexer *last_node)
{
	char	*result;

	result = NULL;
	if (last_node->prev && last_node->prev->str)
		result = ft_strdup(last_node->prev->str);
	else if (last_node->prev && last_node->prev->token)
		result = ft_strdup(last_node->prev->token);
	if (last_node->str)
		result = ft_strjoin(result, last_node->str);
	else if (last_node->token)
		result = ft_strjoin(result, last_node->token);
	return (result);
}

static void	add_merged_node(t_prompt *prompt, char *merged_str)
{
	if (merged_str)
	{
		if (!prompt->lexer)
			prompt->lexer = ms_lstnew(merged_str, 'w');
		else
			ms_lstadd(prompt->lexer, ms_lstnew(merged_str, 'w'));
		free(merged_str);
	}
}

/*Merge last node from the lexer with the previous*/
void	merge_nodes(t_prompt *prompt)
{
	t_lexer	*last_node;
	char	*merged_str;

	last_node = ms_lstlast(prompt->lexer);
	merged_str = merge_str_tokens(last_node);
	del_nodes(prompt, prompt->lexer);
	add_merged_node(prompt, merged_str);
}
