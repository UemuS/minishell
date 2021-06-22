/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 04:09:26 by laafilal          #+#    #+#             */
/*   Updated: 2021/06/07 19:41:38 by laafilal         ###   ########.fr       */
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
		free((void *)str[i]);
		i--;
	}
	free((void *)str);
	return (NULL);
}

int	ft_check_delim(char const *s, char c)
{
	int	j;

	j = 0;
	while (s[j])
	{
		if (s[j] != c)
			break ;
		j++;
	}
	return (j);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	str = malloc(sizeof(char *) * (ft_wcount(s, c) + 1));
	if (!str)
		return (NULL);
	while (i < ft_wcount(s, c))
	{
		j = ft_check_delim(s, c);
		str[i] = ft_substr(s, j, ft_getwordi(s + j, c));
		if (!str[i])
			return (ft_memfree(str, i));
		j = j + ft_getwordi(s + j, c);
		i++;
	}
	str[i] = 0;
	return (str);
}
