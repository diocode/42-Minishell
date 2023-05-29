/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviornment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:52:50 by digoncal          #+#    #+#             */
/*   Updated: 2023/05/29 17:11:04 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	setup_env(t_info *info)
{
	info->pid = NULL;
}

void	reset_env(t_info *info)
{
	/*Do: clear simple cmds*/
	free(info->args);
	if (info->pid)
		free(info->pid);
	/*Do: clear paths's array?*/
	setup_env(info);
	/*tools reset? TBD */
	ms_loop(info);
}
