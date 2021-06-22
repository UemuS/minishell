/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:29:52 by laafilal          #+#    #+#             */
/*   Updated: 2021/06/07 19:10:03 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	l;
	char	*dst;

	l = 0;
	dst = (char *)malloc(ft_strlen(s1) + 1);
	if (dst == NULL)
		return (NULL);
	while (s1[l])
	{
		dst[l] = s1[l];
		l++;
	}
	dst[l] = '\0';
	return (dst);
}
