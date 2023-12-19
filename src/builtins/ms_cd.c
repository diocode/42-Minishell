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

static void	add_path(t_prompt *prompt)
{
	int		i;
	char	*tmp;
	char	*oldpath;
	char	*cwd;

	i = -1;
	oldpath = ms_getenv("PWD", prompt->env);
	while (prompt->env[++i])
	{
		if (!ft_strncmp(prompt->env[i], "PWD=", 4))
		{
			cwd = getcwd(NULL, 0);
			tmp = ft_strjoin("PWD=", cwd);
			free(prompt->env[i]);
			free(cwd);
			prompt->env[i] = tmp;
		}
		else if (!ft_strncmp(prompt->env[i], "OLDPWD=", 7))
		{
			tmp = ft_strjoin("OLDPWD=", oldpath);
			free(prompt->env[i]);
			prompt->env[i] = tmp;
		}
	}
	free(oldpath);
}

static void	ms_cd_utils(t_prompt *prompt)
{
	char	*tmp;

	tmp = ms_getenv("OLDPWD", prompt->env);
	ft_printf("%s\n", tmp);
	free(tmp);
}

static int	cd_utils(t_simple_cmds *simple_cmds)
{
	int	decree;

	decree = chdir(simple_cmds->str[1]);
	if (decree != 0)
	{
		ft_putstr_fd("minishell$: ", STDERR_FILENO);
		ft_putstr_fd(simple_cmds->str[1], STDERR_FILENO);
		perror(" ");
	}
	return (decree);
}

int	ms_cd(t_prompt *prompt, t_simple_cmds *simple_cmds)
{
	int		decree;

	if (!simple_cmds->str[1])
		decree = change_path(prompt, "HOME");
	else if (!ft_strncmp(simple_cmds->str[1], "-", 1))
	{
		decree = change_path(prompt, "OLDPWD");
		if (decree == 0)
			ms_cd_utils(prompt);
	}
	else if (simple_cmds->str[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	else
		decree = cd_utils(simple_cmds);
	if (decree != 0)
		return (1);
	add_path(prompt);
	return (decree);
}
