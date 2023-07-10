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

void	execute_builtin(t_prompt *prompt)
{
	if (!(ft_strncmp(prompt->env[0], "env\0", 4)))
		ms_env(prompt);
	if (!(ft_strncmp(prompt->env[0], "pwd\0", 4)))
		ms_pwd(prompt);
	if (!(ft_strncmp(prompt->env[0], "cd\0", 3)))
		ms_cd(prompt);
	/*if (!ft_strncmp(prompt->env[0], "echo\0", 5))
		ms_echo(prompt);
	if (!(ft_strncmp(prompt->env[0], "export\0", 7)))
		ms_export(prompt);
	if (!(ft_strncmp(prompt->env[0], "unset\0", 6)))
		ms_unset(prompt);
	if (!(ft_strncmp(prompt->env[0], "exit\0", 5)))
		ms_exit_builtins(prompt);
*/
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
