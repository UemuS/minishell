/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notbuilt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan <yihssan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:24:19 by yihssan           #+#    #+#             */
/*   Updated: 2021/06/16 17:24:20 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isflag(char *line)
{
	int	i;

	i = 1;
	if (!ft_strncmp(line, "-n", 2))
	{
		while (line[i] && line[i] == 'n')
			i++;
		if (!line[i])
			return (1);
	}
	return (0);
}

char	*ft_strjoin3(char *s1, char *s2)
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
	free(s1);
	return (str);
}

int	ft_doenv(t_d_list *env)
{
	t_d_list	*head;
	char		*alias;
	char		*value;

	head = env;
	while (head)
	{
		alias = ft_env(head->content)->alias;
		value = ft_env(head->content)->value;
		write(1, alias, ft_strlen(alias));
		write(1, "=", 1);
		write(1, value, ft_strlen(value));
		write(1, "\n", 1);
		head = head->next;
	}
	return (0);
}

int	ft_cutmiddle(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (i);
}
