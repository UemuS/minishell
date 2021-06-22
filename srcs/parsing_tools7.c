/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools7.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan <yihssan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 08:14:16 by yihssan           #+#    #+#             */
/*   Updated: 2021/06/16 13:55:23 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin2(char *s1, char *s2)
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
	free(s2);
	return (str);
}

char	*ft_appendenv2(char *line, t_minishell *mysh, int *i, int *j)
{
	char	*var;

	if (line[(*i) + 1] && ft_validvar(line[(*i) + 1], 1))
	{
		var = ft_substr(line, (*i) + 1, ft_varlength(line + (*i) + 1));
		var = ft_addbcksp(var, mysh->env);
		*j = (*i) + ft_varlength(line + (*i) + 1) + 1;
	}
	else if (line[(*i) + 1] && (ft_isdigit(line[(*i) + 1])
			|| line[(*i) + 1] == '?'))
	{
		var = ft_substr(line, (*i) + 1, 1);
		var = ft_addbcksp(var, mysh->seenv);
		*j = (*i) + 2;
	}
	else
	{
		var = ft_strdup("");
		*j = (*i) + 1;
		if (quotes(line, *i) || !line[*i + 1] || (!(line[*i + 1] == '\"')
				&& !(line[*i + 1] == '\'')))
			(*i)++;
	}
	return (var);
}

char	*ft_appendenv(char *line, t_minishell *mysh)
{
	int		i;
	int		j;
	char	*var;
	char	*buf;

	i = 0;
	while (i < (int)ft_strlen(line) && line && line[i])
	{
		if (quotes(line, i) != 2 && line[i] == '$'
			&& (!i || !(dblquotes(line, i - 1) % 2)))
		{
			var = ft_appendenv2(line, mysh, &i, &j);
			buf = ft_substr(line, 0, i);
			buf = ft_strjoin2(buf, var);
			buf = ft_strjoin2(buf, ft_substr(line, j, ft_strlen(line)));
			free(line);
			line = buf;
		}
		if (quotes(line, i) == 2 || line[i] != '$'
			|| (i && (dblquotes(line, i - 1) % 2)))
			i++;
	}
	return (line);
}

char	*space_line(char *line, t_minishell *mysh)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	line = ft_appendenv(ft_strdup(line), mysh);
	new = space_alloc(line);
	while (new && line[i])
	{
		if (quotes(line, i) == 0 && sep_stuff(line, i))
		{
			new[j++] = ' ';
			new[j++] = line[i++];
			if (quotes(line, i) == 0 && line[i] == '>')
				new[j++] = line[i++];
			new[j++] = ' ';
		}
		else
			new[j++] = line[i++];
	}
	new[j] = '\0';
	free(line);
	return (new);
}

char	*space_line2(char *line, t_minishell *mysh)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	line = ft_appendenv(ft_strdup(line), mysh);
	new = space_alloc(line);
	while (new && line[i])
	{
		if (quotes(line, i) == 0 && sep_stuff(line, i))
		{
			new[j++] = ' ';
			new[j++] = line[i++];
			if (quotes(line, i) == 0 && line[i] == '>')
				new[j++] = line[i++];
			new[j++] = ' ';
		}
		else
			new[j++] = line[i++];
	}
	new[j] = '\0';
	free(line);
	return (new);
}
