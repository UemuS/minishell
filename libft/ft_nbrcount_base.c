/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrcount_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 19:30:01 by laafilal          #+#    #+#             */
/*   Updated: 2020/11/27 19:30:27 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nbrcount_base(unsigned long long n, size_t base)
{
	size_t	c;

	c = 0;
	if (n < base)
		return (c + 1);
	else
	{
		while (n >= base)
		{
			c += ft_nbrcount_base(n % base, base);
			n = n / base;
		}
	}
	return (++c);
}
