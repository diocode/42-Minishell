/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaiva-l <rpaiva-l@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:04:51 by rpaiva-l          #+#    #+#             */
/*   Updated: 2023/08/02 12:56:38 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

void	exit_env(t_prompt *prompt)
{
	g_status = 6;
	printf("exit\n");
	free_data(prompt);
	exit(g_status);
}

void	ms_env(t_prompt *prompt)
{
	int	i;

	i = -1;
	while (prompt->env[++i])
		ft_putendl_fd(prompt->env[i], STDOUT_FILENO);
}
