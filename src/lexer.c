/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:14:26 by digoncal          #+#    #+#             */
/*   Updated: 2023/07/14 16:34:15 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_separator(t_prompt *prompt, char **line_ptr)
{
	if (!ft_strncmp(*line_ptr, "<<", 2))
	{
		prompt->redict_flg = true;
		return (append_separator(prompt, "<<", line_ptr));
	}
	else if (!ft_strncmp(*line_ptr, ">>", 2))
		return (append_separator(prompt, ">>", line_ptr));
	else if (!ft_strncmp(*line_ptr, "<", 1))
		return (append_separator(prompt, "<", line_ptr));
	else if (!ft_strncmp(*line_ptr, ">", 1))
		return (append_separator(prompt, ">", line_ptr));
	else if (!ft_strncmp(*line_ptr, "|", 1))
		return (append_separator(prompt, "|", line_ptr));
	else
		return (1);
}

static int	handle_tokenize(t_prompt *prompt, char *str)
{
	int		error;

	error = 0;
	while (*str)
	{
		if (error)
			return (1);
		if (is_whitespace(*str))
			skip_spaces(&str);
		if (!ft_strncmp(str, "<", 1) || !ft_strncmp(str, ">", 1)
			|| !ft_strncmp(str, "|", 1))
			error = handle_separator(prompt, &str);
		else if (!ft_strncmp(str, "$", 1) && !prompt->redict_flg)
			error = append_doll_sign(prompt, &str);
		else
		{
			error = append_identifier(prompt, &str, -1);
			prompt->redict_flg = false;
		}
		if (prompt->merge)
		{
			merge_nodes(prompt);
			prompt->merge = false;
		}
		//CODE NOT WORKING -> "echo $9$?I$SER$2USER$USER$SER$USER" THE FLAG IS NOT BEING TRIGGERED AT THE RIGHT TIME
		if (*str && !is_whitespace(*str) /*&& prompt->lexer && prompt->lexer->next*/)
			prompt->merge = true;
	}
	return (0);
}

int	lexer(t_prompt *prompt, char *input)
{
	int	flg;

	if (!input[0])
		return (1);
	flg = handle_tokenize(prompt, input);
	free(input);
	if (flg || !prompt->lexer)
		return (1);
	return (0);
}
