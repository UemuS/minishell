/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 14:51:07 by laafilal          #+#    #+#             */
/*   Updated: 2021/06/14 18:38:02 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_wcount2(char *path, char ch)
{
	int		i;
	int		c;

	i = 0;
	c = 1;
	while (path[i])
	{
		if (path[i] == ch)
			c++;
		i++;
	}
	return (c);
}

void	cut_path(char ***paths, char *str, char c, int w)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	start = 0;
	while (i < w - 1)
	{
		(*paths)[i] = ft_strdup("\0");
		while (1)
		{
			if (!str[j] || str[j] == c)
			{
				free((*paths)[i]);
				(*paths)[i] = ft_substr(str, start, j - start);
				start = ++j;
				break ;
			}
			j++;
		}
		i++;
	}
	(*paths)[i] = NULL;
}

char	**ft_split2(char *str, char c)
{
	int		w;
	char	**paths;

	if (!str)
		return (NULL);
	w = ft_wcount2(str, ':') + 1;
	paths = malloc(sizeof(char *) * w);
	if (!paths)
		return (NULL);
	cut_path(&paths, str, c, w);
	return (paths);
}
