/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 19:17:52 by laafilal          #+#    #+#             */
/*   Updated: 2021/06/07 19:10:20 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		l;
	size_t		i;
	size_t		odest;
	size_t		osrc;

	l = 0;
	osrc = ft_strlen(src);
	if (size == 0 && !dst)
		return (ft_strlen(src));
	i = ft_strlen(dst);
	odest = i;
	if (size <= odest)
		return (osrc + size);
	while (l < (size - odest - 1) && src[l])
	{
		dst[i] = src[l];
		i++;
		l++;
	}
	dst[i] = '\0';
	return (odest + osrc);
}
