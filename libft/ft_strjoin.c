/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan <yihssan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 00:22:53 by laafilal          #+#    #+#             */
/*   Updated: 2021/04/19 08:51:53 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	l;
	size_t	i;
	size_t	som;

	l = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	som = (ft_strlen(s1) + 1 + 1);
	str = malloc(som);
	if (!str)
		return (NULL);
	while (l < som - 1)
	{
		if (l < ft_strlen(s1))
			str[l] = s1[l];
		else
			str[l] = s2[i++];
		l++;
	}
	str[l] = '\0';
	return (str);
}
