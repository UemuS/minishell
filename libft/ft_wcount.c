/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcount.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 15:49:34 by laafilal          #+#    #+#             */
/*   Updated: 2021/06/07 19:28:12 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wcount(char const *s, char c)
{
	size_t	k;
	size_t	i;
	char	m[2];

	m[0] = c;
	m[1] = '\0';
	k = 0;
	i = 0;
	s = ft_strtrim(s, m);
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if ((s[i] == c && s[i - 1] != c) || (s[i] != c && s[i + 1] == '\0'))
			k++;
		i++;
	}
	free((void *)s);
	return (k);
}
