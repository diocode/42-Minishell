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

static t_token *get_redirect(void)
{
	if (!ms()->process->redirect)
	{
		ms()->process->redirect = malloc(sizeof(t_token));
		if (!ms()->process->redirect)
			return (g_exit_code = 1, ms_exit(NULL), NULL);
	}
	else
	{
		ms()->process->redirect->next = malloc(sizeof(t_process));
		if (!ms()->process->redirect->next)
			return (g_exit_code = 1, ms_exit(NULL), NULL);
		ms()->process->redirect->next->prev = ms()->process->redirect;
		ms()->process->redirect = ms()->process->redirect->next;
		ms()->process->next = NULL;
	}
	ms()->process->redirect->type = ms()->lexer->type;
	ms()->lexer = ms()->lexer->next;
	ms()->process->redirect->content = ft_strdup(ms()->lexer->content);
	if (!ms()->process->redirect->content)
		return (g_exit_code = 1, ms_exit(NULL), NULL);
	ms()->lexer = ms()->lexer->next;
	return (NULL);
}

static char	**get_args(void)
{
	t_token	*tmp;
	char	**args;
	size_t	i;

	tmp = ms()->lexer;
	i = 0;
	while (tmp && tmp->type == OTHER)
	{
		i++;
		tmp = tmp->next;
	}
	args = ft_calloc(i + 1, sizeof(char *));
	if (!args)
		return (g_exit_code = 1, ms_exit(NULL), NULL);
	i = -1;
	while (ms()->lexer && ms()->lexer->type == OTHER)
	{
		args[++i] = ft_strdup(ms()->lexer->content);
		if (!args[i])
			return (g_exit_code = 1, free_array(args), ms_exit(NULL), NULL);
		ms()->lexer = ms()->lexer->next;
	}
	return (args);
}

static void	parse_content(void)
{
	while (ms()->lexer && ms()->lexer->type != PIPE)
	{
		if (ms()->lexer->type == OTHER)
		{
			if (is_builtin(ms()->lexer->content))
			{
				ms()->process->builtin = ft_strdup(ms()->lexer->content);
				ms()->lexer = ms()->lexer->next;
			}
			else
				ms()->process->args = get_args();
		}
		else if (ms()->lexer && ms()->lexer->type != PIPE)
			ms()->process->redirect = get_redirect();
	}
	if (ms()->lexer && ms()->lexer->type == PIPE)
		ms()->lexer = ms()->lexer->next;
}

static int	generate_process(void)
{
	if (!ms()->process)
	{
		ms()->process = malloc(sizeof(t_process));
		if (!ms()->process)
			return (ms_error(1), 1);
	}
	else
	{
		ms()->process->next = malloc(sizeof(t_process));
		if (!ms()->process->next)
			return (ms_error(1), 1);
		ms()->process->next->prev = ms()->process;
		ms()->process = ms()->process->next;
		ms()->process->next = NULL;
	}
	ms()->process->args = NULL;
	ms()->process->builtin = NULL;
	ms()->process->redirect = NULL;
	ms()->process->hd_file = NULL;
	parse_content();
	return (0);
}

int	parser(void)
{
	int			pipes;

	if (expander())
		return (1);
	if(pipe_error() || token_error() || redirection_error())
		return (1);
	trim_quotes();
	pipes = count_pipes(ms()->lexer);
	while (pipes >= 0)
	{
		if (generate_process())
			return (1);
		pipes--;
	}
	while (ms()->process && ms()->process->prev)
		ms()->process = ms()->process->prev;
	return (0);
}
