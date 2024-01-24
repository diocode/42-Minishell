/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 20:47:13 by digoncal          #+#    #+#             */
/*   Updated: 2024/01/21 20:47:13 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_code;

static int	redirect_errors(void)
{
	t_token		*tmp;

	tmp = ms()->lexer;
	while (tmp)
	{
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT
			|| tmp->type == REDIR2_OUT || tmp->type == HEREDOC)
		{
			if (tmp->next && tmp->next->content && !tmp->next->content[0])
			{
				g_exit_code = 1;
				ft_putstr_fd("minishell: ambiguous redirect\n", STDERR_FILENO);
				return (1);
			}
			if (!tmp->next || (tmp->next && !tmp->next->content))
			{
				g_exit_code = 2;
				ft_putstr_fd("minishell: syntax error "
					"near unexpected token `newline'\n", STDERR_FILENO);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

static int	token_errors(void)
{
	t_token		*tmp;

	if (redirect_errors())
		return (1);
	tmp = ms()->lexer;
	while (tmp)
	{
		if (tmp->type == PIPE
			&& (!tmp->prev ||!tmp->next || tmp->next->type == PIPE))
		{
			g_exit_code = 2;
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
			if (tmp->next && tmp->next->type == PIPE)
				ft_putstr_fd(tmp->next->content, STDERR_FILENO);
			else
				ft_putstr_fd(tmp->content, STDERR_FILENO);
			ft_putstr_fd("'\n", STDERR_FILENO);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

/*static t_token	*get_curr_process(int pipes)
{
	t_token		*tmp;

	tmp = ms()->lexer;
	while (tmp)
	{
		if (tmp ->)
		tmp = tmp->next;
	}
	return (ms()->lexer);
}*/

/*static int	generate_process(int pipes)
{
	t_token		*tmp;

	tmp = get_curr_process(pipes);
	return (0);
}*/

void	parser(void)
{
	int			pipes;

	expander();
	if(token_errors())
		return ;
	pipes = count_pipes(ms()->lexer);
	while (pipes >= 0)
	{
		printf("pipes: %d\n", pipes);
		/*if (generate_process(pipes))
			break ;*/
		pipes--;
	}
}
