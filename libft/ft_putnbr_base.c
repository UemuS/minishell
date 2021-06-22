/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 19:23:38 by laafilal          #+#    #+#             */
/*   Updated: 2020/11/27 19:37:10 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base(unsigned long long nb, char *base)
{
	size_t	len_base;

	len_base = ft_strlen(base);
	if (nb >= len_base)
		ft_putnbr_base((nb / len_base), base);
	ft_putchar_fd(base[nb % len_base], 1);
}
