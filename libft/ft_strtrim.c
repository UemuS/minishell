/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <afilal.lamiaa@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 01:47:16 by laafilal          #+#    #+#             */
/*   Updated: 2020/12/28 17:09:30 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		ft_trim_front(const char *str, char const *set)
{
	size_t		i;
	size_t		c;

	i = 0;
	c = 0;
	while (str[i] != '\0')
	{
		if (!ft_strchr(set, str[i++]))
			return (c);
		c++;
	}
	return (c);
}

static size_t		ft_trim_back(const char *str, char const *set)
{
	size_t		i;
	size_t		c;

	i = ft_strlen(str) - 1;
	c = 0;
	while (i + 1 > 0 && str[i] != '\0')
	{
		if (!ft_strchr(set, str[i--]))
			return (c);
		c++;
	}
	return (i);
}

char				*ft_strtrim(char const *s1, char const *set)
{
	char		*str;
	size_t		ctf;
	size_t		ctb;

	if (!s1)
		return (NULL);
	if (!set || *s1 == 0 || *set == 0)
		return (ft_strdup(s1));
	ctf = ft_trim_front(s1, set);
	ctb = ft_strlen(s1) - (ft_trim_front(s1, set) + ft_trim_back(s1, set));
	str = ft_substr(s1, ctf, ctb);
	if (!str)
		return (NULL);
	return (str);
}
