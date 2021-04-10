/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <afilal.lamiaa@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 22:43:10 by laafilal          #+#    #+#             */
/*   Updated: 2019/11/20 11:02:22 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	l;

	l = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	len = ((start + len) > ft_strlen(s) ? (ft_strlen(s) - start) : len);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	while (l < len)
		str[l++] = s[start++];
	str[l] = '\0';
	return (str);
}
