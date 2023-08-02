/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_input_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:46:27 by digoncal          #+#    #+#             */
/*   Updated: 2023/07/04 17:46:27 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	qts_nbr(t_prompt *prompt, char const *str, int i, int size)
{
	int	j;
	int	quotes;

	quotes = 0;
	j = 0;
	while (j <= size)
	{
		if (str[i + j] == '"' || str[i + j] == '\'')
		{
			check_flg(prompt, str, i + j);
			if ((str[i + j] == '"' && prompt->flg[1])
				|| (str[i + j] == '\'' && prompt->flg[0]))
				j++;
			else
			{
				quotes++;
				i++;
			}
		}
		else
			j++;
	}
	return (quotes);
}

void	check_flg(t_prompt *p, char const *str, int i)
{
	if (str[i] == '"')
	{
		if (p->flg[0])
			p->flg[0] = 0;
		else if (!p->flg[1])
			p->flg[0] = 1;
	}
	if (str[i] == '\'')
	{
		if (p->flg[1])
			p->flg[1] = 0;
		else if (!p->flg[0])
			p->flg[1] = 1;
	}
}

int	skip_word(t_prompt *prompt, char const *str, int i)
{
	while ((!is_whitespace(str[i]) || prompt->flg[0]
			|| prompt->flg[1]) && str[i])
	{
		i++;
		if (str[i] == '"' && prompt->flg[0])
			prompt->flg[0] = 0;
		if (str[i] == '\'' && prompt->flg[1])
			prompt->flg[1] = 0;
	}
	return (i);
}
