/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 12:50:41 by digoncal          #+#    #+#             */
/*   Updated: 2023/10/26 13:20:44 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strdup(const char *src)
{
	int			i;
	char		*str;

	str = (char *) ft_calloc((ft_strlen((char *)src) + 1), sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (src && src[i])
	{
		str[i] = src[i];
		i++;
	}
	return (str);
}
