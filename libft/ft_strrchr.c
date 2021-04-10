/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <afilal.lamiaa@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 00:13:35 by laafilal          #+#    #+#             */
/*   Updated: 2019/12/05 17:01:36 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	l;
	char	*str;

	l = ft_strlen(s);
	str = (char*)s;
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
