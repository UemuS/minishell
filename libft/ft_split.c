/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <afilal.lamiaa@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 04:09:26 by laafilal          #+#    #+#             */
/*   Updated: 2021/01/10 17:13:16 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_getwordi(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			break ;
		i++;
	}
	return (i);
}

static	char	**ft_memfree(char **str, size_t i)
{
	while (i + 1 > 0)
	{
		free((void*)str[i]);
		i--;
	}
	free((void*)str);
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	char	**str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (!(str = malloc(sizeof(char*) * (ft_wcount(s, c) + 1))))
		return (NULL);
	while (i < ft_wcount(s, c))
	{
		while (s[j])
		{
			if (s[j] != c)
				break ;
			j++;
		}
		if (!(str[i] = ft_substr(s, j, ft_getwordi(s + j, c))))
			return (ft_memfree(str, i));
		j = j + ft_getwordi(s + j, c);
		i++;
	}
	str[i] = 0;
	return (str);
}
