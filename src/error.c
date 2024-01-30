/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 01:43:15 by digoncal          #+#    #+#             */
/*   Updated: 2024/01/30 01:47:27 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_code;

static char	*file_dir_error(char *tmp)
{
	struct stat	st;
	char		*str;

	if (stat(tmp, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
			str = ft_strjoin(tmp, ": Is a directory");
		else if (S_IXUSR)
			str = ft_strjoin(tmp, ": Permission denied");
	}
	else
		str = ft_strjoin(tmp, ": No such file or directory\n");
	return (str);
}

int	error_cmd_not_found(t_process *process)
{
	struct stat	st;
	char		*str;
	char		*tmp;
	int			status;

	status = 127;
	if (!process->args && !process->args[0])
		return (1);
	if (process->args[0][0])
		tmp = ft_strdup(process->args[0]);
	else
		tmp = ft_strdup("\'\'");
	if ((process->args[0][0] == '/' || process->args[0][0] == '.'))
		str = file_dir_error(tmp);
	else
		str = ft_strjoin(tmp, ": command not found");
	ft_putendl_fd(str, STDERR_FILENO);
	if ((process->args[0][0] == '/' || process->args[0][0] == '.')
		&& stat(tmp, &st) == 0 && (S_ISDIR(st.st_mode) | S_IXUSR))
		status = 126;
	free(tmp);
	free(str);
	return (status);
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
