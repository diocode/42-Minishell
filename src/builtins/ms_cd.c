/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:01:09 by digoncal          #+#    #+#             */
/*   Updated: 2024/01/26 19:01:09 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	change_path(char *path)
{
	char	*tmp;
	int		decree;

	tmp = ms_getenv(path);
	if (!tmp)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(" not set\n", STDERR_FILENO);
		return (1);
	}
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

static void	add_path()
{
	t_env 	*env;
	char	*tmp;
	char	*oldpath;

	oldpath = ms_getenv("PWD");
	env = ms()->env;
	while (env)
	{
		if (!ft_strncmp(env->key, "PWD", 4))
		{
			if (env->value)
				free(env->value);
			tmp = getcwd(NULL, 0);
			env->value = ft_strdup(tmp);
			free(tmp);
		}
		else if (!ft_strncmp(env->key, "OLDPWD", 7))
		{
			if (env->value)
				free(env->value);
			env->value = ft_strdup(oldpath);
		}
		env = env->next;
	}
	free(oldpath);
}

static void	ms_cd_utils()
{
	char	*tmp;

	tmp = ms_getenv("OLDPWD");
	ft_printf("%s\n", tmp);
	free(tmp);
}

static int	cd_utils(t_process *process)
{
	int	decree;

	decree = chdir(process->args[0]);
	if (decree != 0)
	{
		ft_putstr_fd("minishell$: ", STDERR_FILENO);
		ft_putstr_fd(process->args[0], STDERR_FILENO);
		perror(" ");
	}
	return (decree);
}

int	ms_cd(t_process *process)
{
	int		decree;

	if (!process->args || !process->args[0] || (process->args[0]
		&& !ft_strncmp(process->args[0], "~", 2) && !process->args[1]))
		decree = change_path("HOME");
	else if (!ft_strncmp(process->args[0], "-", 1))
	{
		decree = change_path("OLDPWD");
		if (decree == 0)
			ms_cd_utils();
	}
	else if (process->args[1])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	else
		decree = cd_utils(process);
	if (decree != 0)
		return (1);
	add_path();
	return (decree);
}
