/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:01:22 by digoncal          #+#    #+#             */
/*   Updated: 2023/08/02 14:43:26 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	change_path(t_prompt *prompt, char *path)
{
	char	*tmp;
	int		decree;

	tmp = ms_getenv(path, prompt->env);
	decree = chdir(tmp);
	free(tmp);
	if (decree != 0)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
	}
	return (decree);
}

void	add_new_path(t_prompt *prompt)
{
	int		i;
	char	*tmp;

	i = -1;
	while (prompt->env[++i])
	{
		if (!ft_strncmp(prompt->simple_cmds->str[1], "PWD=", 4))
		{
			tmp = ft_strjoin("PWD=", prompt->simple_cmds->str[1]);
			free(prompt->env[i]);
			prompt->env[1] = tmp;
		}
		else if (!ft_strncmp(prompt->simple_cmds->str[1], "OLDPWD=", 7)
			&& prompt->simple_cmds->str)
		{
			tmp = ft_strjoin("OLDPWD=", prompt->simple_cmds->str[1]);
			free(prompt->env[i]);
			prompt->env[1] = tmp;
		}
	}
}

int	ms_cd(t_prompt *prompt, t_simple_cmds *simple_cmds)
{
	int	decree;

	if (!simple_cmds->str[1])
		decree = change_path(prompt, "HOME");
	else if (!ft_strncmp(simple_cmds->str[1], "-", 1))
	{
		decree = change_path(prompt, "OLDPWD");
		ft_printf("%s\n", ms_getenv("HOME", prompt->env));
	}
	else
	{
		decree = chdir(simple_cmds->str[1]);
		if (decree != 0)
		{
			ft_putstr_fd("minishell$: ", STDERR_FILENO);
			ft_putstr_fd(simple_cmds->str[1], STDERR_FILENO);
			perror(" ");
		}
	}
	if (decree != 0)
		return (1);
	add_new_path(prompt);
	return (decree);
}
