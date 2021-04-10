/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <afilal.lamiaa@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:32:26 by laafilal          #+#    #+#             */
/*   Updated: 2019/11/20 11:06:51 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	char	*s;

	i = 0;
	s = (char*)src;
	while (s[i] && i + 1 < size)
	{
		dst[i] = s[i];
		i++;
	}
	if (size)
		dst[i] = '\0';
	return (ft_strlen(s));
}
