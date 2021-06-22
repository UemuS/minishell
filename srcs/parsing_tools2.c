/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan <yihssan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 19:53:24 by yihssan           #+#    #+#             */
/*   Updated: 2021/06/08 19:44:00 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_varlength(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_validvar(line[i], 0))
		i++;
	return (i);
}

int	ft_countspe(char *line)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (line && line[++i])
	{
		if (ft_strchr("\'\\\"<>|;", line[i]))
			j += 2;
		else
			j++;
	}
	return (j);
}

char	*ft_addbcksp(char *var, t_d_list *env)
{
	int		i;
	int		j;
	char	*ret;
	char	*line;

	line = ft_get_env(var, env);
	free(var);
	i = ft_countspe(line);
	ret = malloc(sizeof(char *) * i + 1);
	i = 0;
	j = 0;
	while (line && line[i])
	{
		if (ft_strchr("\'\\\"<>|;", line[i]))
		{
			ret[i + (j++)] = '\\';
			ret[i + j] = line[i];
		}
		else
			ret[i + j] = line[i];
		i++;
	}
	ret[i + j] = 0;
	return (ret);
}

t_token	*split_tok(char *line)
{
	t_token	*prev;
	t_token	*next;
	int		i;
	int		sep;

	prev = NULL;
	next = NULL;
	i = 0;
	ft_skip_space(line, &i);
	while (line[i])
	{
		sep = ignore_sep(line, i);
		next = next_token(line, &i);
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
		type_arg(next, sep);
		ft_skip_space(line, &i);
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;
	return (next);
}

void	fill_tok(t_pars *pars, char *line)
{
	pars->start = split_tok(line);
}
