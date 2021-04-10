/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <afilal.lamiaa@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 22:28:27 by laafilal          #+#    #+#             */
/*   Updated: 2020/12/28 15:48:56 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int		ft_atoi(const char *str)
{
	size_t	l;
	long	res;
	int		sign;

	l = 0;
	res = 0;
	sign = 1;
	while (str[l] != '\0' && ((str[l] >= 9 && str[l] <= 13) || str[l] == 32))
		l++;
	if (str[l] == '-')
		sign = -1;
	if (str[l] == '-' || str[l] == '+')
		l++;
	while (str[l] != '\0' && str[l] >= 48 && str[l] <= 57)
	{
		if (res * 10 + str[l] - '0' < res)
		{
			res = (sign == -1 ? 0 : -1);
			break ;
		}
		res = res * 10 + str[l++] - '0';
	}
	return (res * sign);
}
