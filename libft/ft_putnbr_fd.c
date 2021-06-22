/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 20:33:07 by laafilal          #+#    #+#             */
/*   Updated: 2021/06/07 19:05:16 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;
	char	*str;
	size_t	i;

	i = ft_nbrcount(n);
	nb = n;
	str = malloc(sizeof(char *) * (i + 1));
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
	free(str);
}
