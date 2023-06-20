/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:14:26 by digoncal          #+#    #+#             */
/*   Updated: 2023/06/20 12:31:12 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
1. Get first word from input;
2. Determine if it's a word or token;
3. Add word to prompt->lexer using ms_lstnew();
4. Add new node to the end of the list using ms_lstadd();
*/

void	lexer(t_prompt *prompt, char *input)
{
	(void)input;
	(void)prompt;
}
