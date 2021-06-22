/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 21:16:54 by laafilal          #+#    #+#             */
/*   Updated: 2021/06/07 19:32:40 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nbrcount(int n)
{
	int		nbc;
	long	nb;

	nb = n;
	nbc = 0;
	if (nb < 0)
	{
		nb = nb * -1;
		nbc++;
	}
	while (nb >= 10)
	{
		nb = nb / 10;
		nbc++;
	}
	if (nb >= 0 && nb < 10)
		nbc++;
	return (nbc);
}
