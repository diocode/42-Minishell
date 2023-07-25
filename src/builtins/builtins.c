/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaiva-l <rpaiva-l@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:04:51 by rpaiva-l          #+#    #+#             */
/*   Updated: 2023/06/19 20:07:16 by rpaiva-l         ###   ########.fr       */
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

void	ms_pwd(t_prompt *prompt)
{
	int		i;

	i = -1;
	while (prompt->env[++i])
	{
		if (!ft_strncmp(prompt->env[i], "PWD=", 4))
			ft_printf("%s\n", (ft_substr(prompt->env[i], 4,
						ft_strlen(prompt->env[i]) - 4)));
		/*if (!ft_strncmp(prompt->env[i], "OLDPWD=", 7))
			ft_printf("%s\n", (ft_substr(prompt->env[i], 7,
						ft_strlen(prompt->env[i]) - 7)));*/
	}
}

void	ms_cd(t_prompt *prompt)
{
	int	i;

	i = -1;
	while (prompt->env[++i])
	{
		if (!ft_strncmp(prompt->env[i], "PATH=", 5))
			ft_printf("%s\n", (ft_substr(prompt->env[i], 5,
						ft_strlen(prompt->env[i]) - 5)));
	}
}

/*void	ms_echo(t_prompt *prompt)
{
	int	i;

	i = -1;
	while (prompt->env[++i])
	{
		if ()

	}
}

void	ms_export(t_prompt *prompt)
{
}

int	ms_unset(t_prompt *prompt)
{
}

void	ms_exit_builtins(t_prompt *prompt)
{

}
 */
