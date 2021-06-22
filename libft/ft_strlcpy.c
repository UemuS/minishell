/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:32:26 by laafilal          #+#    #+#             */
/*   Updated: 2021/06/07 19:10:33 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	char	*s;

	i = 0;
	s = (char *)src;
	while (s[i] && i + 1 < size)
	{
		dst[i] = s[i];
		i++;
	}
	if (size)
		dst[i] = '\0';
	return (ft_strlen(s));
}
