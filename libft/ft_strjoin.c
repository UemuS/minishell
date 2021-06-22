/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <afilal.lamiaa@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 00:22:53 by laafilal          #+#    #+#             */
/*   Updated: 2019/11/20 11:16:43 by laafilal         ###   ########.fr       */
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
	som = (ft_strlen(s1) + ft_strlen(s2) + 1);
	str = malloc(som);
	if (!str)
		return (NULL);
	while (l < som)
	{
		if (l < ft_strlen(s1))
			str[l] = s1[l];
		else
			str[l] = s2[i++];
		l++;
	}
	return (str);
}
