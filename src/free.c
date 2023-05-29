/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:29:47 by digoncal          #+#    #+#             */
/*   Updated: 2023/05/29 16:20:26 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_info(t_info *info)
{
	if (!info)
		return ;
	if (info->env)
		free_array(info->env);
	if (info->pwd)
		free (info->pwd);
	if (info->old_pwd)
		free (info->old_pwd);
	if (info->args || !info->args[0])
		free(info->args);
	if (info->pid)
		free(info->pid);
	free(info);
}
