/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools8.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan <yihssan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 13:08:44 by yihssan           #+#    #+#             */
/*   Updated: 2021/06/09 13:11:09 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *head)
{
	while (head)
	{
		free(head->str);
		if (head->next)
		{
			head = head->next;
			free(head->prev);
		}
		else
		{
			free(head);
			break ;
		}
	}
}

int	ft_nextline(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] != ';' || quotes(line, i)
			|| (i && dblquotes(line, i - 1) % 2)))
		i++;
	return (i);
}

int	ft_nextlineexist(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] != ';'
			|| quotes(line, MAX_INT) || (i && dblquotes(line, i - 1) % 2)))
		i++;
	if (line[i])
	{
		i++;
		while (line[i])
		{
			if (line[i] != ' ')
				return (1);
			i++;
		}
	}
	return (0);
}

char	*ft_cutline(char *line)
{
	char	*ret;
	int		i;

	i = ft_nextline(line);
	ret = ft_substr(line, 0, i);
	return (ret);
}

char	*ft_substr2(char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	l;

	l = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if ((start + len) > ft_strlen(s))
		len = (ft_strlen(s) - start);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	while (l < len)
		str[l++] = s[start++];
	str[l] = '\0';
	free(s);
	return (str);
}
