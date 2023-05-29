/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:02:19 by digoncal          #+#    #+#             */
/*   Updated: 2023/05/26 16:37:37 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	find_pwd(t_info *info)
{
	int	i;

	i = -1;
	while (info->env[++i])
	{
		if (!ft_strncmp(info->env[i], "PWD=", 4))
			info->pwd = ft_substr(info->env[i], 4, ft_strlen(info->env[i]) - 4);
		if (!ft_strncmp(info->env[i], "OLDPWD=", 7))
			info->old_pwd = ft_substr(info->env[i], 7,
					ft_strlen(info->env[i]) - 7);
	}
}
