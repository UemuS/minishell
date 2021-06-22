/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 14:39:35 by laafilal          #+#    #+#             */
/*   Updated: 2021/06/17 15:43:46 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	overflow_handler(int sign)
{
	long	res;

	if (sign == -1)
		res = 0;
	else
		res = -1;
	errno = 34;
	return (res);
}

long	ft_atol(const char *str)
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
		sign = -1, l++;
	if (str[l] == '-' || str[l] == '+')
		errno = 22, l++;
	if (!(str[l] >= 48 && str[l] <= 57))
		errno = 22;
	while (str[l] != '\0' && str[l] >= 48 && str[l] <= 57)
	{
		if ((res * 10 + (str[l] - '0') * sign > res && sign == -1)
			|| (res * 10 + (str[l] - '0') * sign < res && sign == 1))
			return (overflow_handler(sign));
		res = res * 10 + (str[l++] - '0') * sign;
	}
	return (res);
}
