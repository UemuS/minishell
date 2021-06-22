/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan <yihssan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:24:30 by yihssan           #+#    #+#             */
/*   Updated: 2021/06/16 17:24:31 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_cmd(void *content)
{
	return (content);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	free_tokens2(t_minishell *head)
{
	int	i;

	while (head->cmd)
	{
		i = -1;
		free(ft_cmd(head->cmd->content)->str);
		free(ft_cmd(head->cmd->content)->input);
		free(ft_cmd(head->cmd->content)->output);
		while (ft_cmd(head->cmd->content)->args
			&& ft_cmd(head->cmd->content)->args[++i])
			free(ft_cmd(head->cmd->content)->args[i]);
		if (ft_cmd(head->cmd->content)->args)
			free(ft_cmd(head->cmd->content)->args);
		free(head->cmd->content);
		if (head->cmd->next)
		{
			head->cmd = head->cmd->next;
			free(head->cmd->prev);
		}
		else
		{
			free(head->cmd);
			break ;
		}
	}
}

int	bslquotes(char *line, int *i)
{
	if (line[*i + 1] == '\"' || line[*i + 1] == '$')
		return (1);
	else if (line[*i + 1] == '\\')
		return (1);
	else
		return (0);
}
