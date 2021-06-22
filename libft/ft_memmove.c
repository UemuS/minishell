/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 23:07:10 by laafilal          #+#    #+#             */
/*   Updated: 2021/06/07 19:01:47 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	l;

	l = 0;
	if (dst < src)
	{
		while (l < len)
		{
			((unsigned char *)dst)[l] = ((unsigned char *)src)[l];
			l++;
		}
	}
	else if (dst > src)
	{
		len--;
		while (len + 1 > 0)
		{
			((unsigned char *)dst)[len] = ((unsigned char *)src)[len];
			len--;
		}
	}
	return (dst);
}
