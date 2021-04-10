/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <afilal.lamiaa@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 20:33:07 by laafilal          #+#    #+#             */
/*   Updated: 2019/11/20 11:26:29 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;
	char	str[ft_nbrcount(n)];
	size_t	i;

	i = ft_nbrcount(n);
	nb = n;
	if (nb < 0)
	{
		nb = nb * -1;
		str[0] = '-';
	}
	str[i] = '\0';
	i--;
	while (nb >= 10)
	{
		str[i] = (nb % 10) + '0';
		nb = nb / 10;
		i--;
	}
	if (nb >= 0 && nb < 10)
		str[i] = nb + '0';
	ft_putstr_fd(str, fd);
}
