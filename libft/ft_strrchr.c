/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 00:13:35 by laafilal          #+#    #+#             */
/*   Updated: 2021/06/07 19:13:39 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	l;
	char	*str;

	l = ft_strlen(s);
	str = (char *)s;
	if (c == str[l])
		return (str + l);
	l--;
	while (l + 1 > 0 && str[l])
	{
		if (str[l] == c)
			return (str + l);
		l--;
	}
	return (NULL);
}
