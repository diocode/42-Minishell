/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 09:31:51 by digoncal          #+#    #+#             */
/*   Updated: 2023/10/31 14:12:10 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*str;

	if (!s)
		return (0);
	if (start >= (unsigned int)ft_strlen((char *)s))
	{
		str = (char *) ft_calloc(1, 1);
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	str = (char *) ft_calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s[start] && len--)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
