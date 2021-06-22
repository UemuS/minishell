/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <afilal.lamiaa@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 18:26:19 by laafilal          #+#    #+#             */
/*   Updated: 2019/12/05 15:43:33 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			l;

	l = 0;
	while (l < n)
	{
		if (((unsigned char *)s)[l] == (unsigned char)c)
			return ((unsigned char *)s + l);
		l++;
	}
	return (NULL);
}
