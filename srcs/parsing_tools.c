/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan <yihssan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:24:24 by yihssan           #+#    #+#             */
/*   Updated: 2021/06/16 17:24:25 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dblquotes(char *line, int i)
{
	int	j;

	j = 0;
	while (i >= 0 && line[i] == '\\')
	{
		i--;
		j++;
	}
	return (j);
}

int	sep_stuff(char *line, int i)
{
	if (i > 0 && line[i - 1] == '\\' && ft_strchr("<>|;", line[i]))
		return (0);
	else if (ft_strchr("<>|;", line[i]) && quotes(line, i) == 0)
		return (1);
	else
		return (0);
}

int	ignore_sep(char *line, int i)
{
	bool	bol;

	bol = dblquotes(line, i);
	if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == ';')
		return (bol);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '|')
		return (bol);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>')
		return (bol);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>'
		&& line[i + 2] && line[i + 2] == '>')
		return (bol);
	return (0);
}

int	quotes(char *line, int index)
{
	int	i;
	int	open;
	int	j;

	j = 0;
	i = 0;
	open = 0;
	while (line[i] && i != index)
	{
		if (i > 0 && line[i - 1] == '\\' && open == 1 && line[i] == '\"')
			j = dblquotes(line, i - 1);
		if (i > 0 && (dblquotes(line, i - 1) % 2) && open == 0)
			;
		else if (open == 0 && line[i] == '\"')
			open = 1;
		else if (open == 0 && line[i] == '\'')
			open = 2;
		else if (open == 1 && line[i] == '\"' && !(j % 2))
			open = 0;
		else if (open == 2 && line[i] == '\'')
			open = 0;
		i += 1;
		j = 0;
	}
	return (open);
}
