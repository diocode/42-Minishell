/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:10:25 by digoncal          #+#    #+#             */
/*   Updated: 2024/01/23 12:10:25 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_code;

int	export_error(char *c)
{
	ft_putstr_fd("export: ", STDERR_FILENO);
	if (c)
	{
		ft_putchar_fd('\'', STDERR_FILENO);
		ft_putstr_fd(c, STDERR_FILENO);
		ft_putstr_fd("\': ", STDERR_FILENO);
	}
	ft_putendl_fd("not a valid identifier", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	token_error(void)
{
	t_token		*tmp;

	tmp = ms()->lexer;
	while (tmp)
	{
		if (tmp->type != PIPE && tmp->type != OTHER)
		{
			if (!tmp->next || (tmp->next && tmp->next->type == PIPE))
			{
				ft_putstr_fd("minishell: syntax error near ", STDERR_FILENO);
				ft_putstr_fd("unexpected token `newline'\n", STDERR_FILENO);
				return (g_exit_code = 2, 1);
			}
			else if (tmp->next && tmp->next->type != OTHER)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd("syntax error near unexpected token `", 2);
				ft_putstr_fd(tmp->next->content, STDERR_FILENO);
				ft_putstr_fd("'\n", STDERR_FILENO);
				return (g_exit_code = 2, 1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	redirection_error(void)
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
		}
		tmp = tmp->next;
	}
	return (0);
}

int	pipe_error(void)
{
	t_token		*tmp;

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

void	ms_error(int error)
{
	g_exit_code = error;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (error == 1)
		ft_putstr_fd("memory error: unable to assign memory\n", STDERR_FILENO);
	else if (error == 2)
		ft_putstr_fd("syntax error: unable to locate closing quotation\n",
			STDERR_FILENO);
	else if (error == 3)
		ft_putstr_fd("Parser problem\n", STDERR_FILENO);
	else if (error == 4)
		ft_putstr_fd("Failed to create pipe\n", STDERR_FILENO);
	else if (error == 5)
		ft_putstr_fd("Failed to fork\n", STDERR_FILENO);
	else if (error == 6)
		ft_putstr_fd("outfile: Error\n", STDERR_FILENO);
	else if (error == 7)
		ft_putstr_fd("infile: No such file or directory\n", STDERR_FILENO);
	else if (error == 8)
		ft_putendl_fd("Path does not exist\n", STDERR_FILENO);
}
