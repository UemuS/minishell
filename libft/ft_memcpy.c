/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <afilal.lamiaa@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 21:48:00 by laafilal          #+#    #+#             */
/*   Updated: 2019/12/05 15:21:26 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		l;

	l = 0;
	if (src != dst)
	{
		while (l < n)
		{
			((unsigned char*)dst)[l] = ((unsigned char*)src)[l];
			l++;
		}
	}
	return (dst);
}
