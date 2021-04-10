/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <afilal.lamiaa@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 23:59:17 by laafilal          #+#    #+#             */
/*   Updated: 2019/12/17 21:21:15 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	l;
	char	*str;

	l = 0;
	str = (char*)s;
	while (str[l])
	{
		if (str[l] == c)
			return (str + l);
		l++;
	}
	if (c == str[l])
		return (str + l);
	return (NULL);
}
