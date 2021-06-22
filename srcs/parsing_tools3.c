/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan <yihssan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:24:28 by yihssan           #+#    #+#             */
/*   Updated: 2021/06/16 17:24:29 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_skip_space(const char *str, int *i)
{
	while ((str[*i] == ' ' || str[*i] == '\t')
		|| (str[*i] == '\r' || str[*i] == '\v' || str[*i] == '\f'))
		(*i)++;
}

int	ft_validvar(char c, int i)
{
	if (i == 0 && (c == '_' || ft_isalpha(c) || ft_isdigit(c)))
		return (1);
	if (i == 1 && (c == '_' || ft_isalpha(c)))
		return (1);
	return (0);
}

void	next_tokens2(char *line, int *i, int *j, t_token *token)
{
	char	c;

	c = ' ';
	while (line[*i] && (line[*i] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i] == '\'' || line[*i] == '\"'))
			c = line[(*i)++];
		else if (c != ' ' && line[*i] == c)
		{
			c = ' ';
			(*i)++;
		}
		else if (line[*i] == '\\')
		{
			if ((quotes(line, *i) != 2) && (quotes(line, *i) != 1
					|| (line[(*i) + 1] && bslquotes(line, i))))
				(*i)++;
			token->str[(*j)++] = line[*i];
			(*i) += (line[*i] != 0);
		}
		else
			token->str[(*j)++] = line[(*i)++];
	}
}

t_token	*next_token(char *line, int *i)
{
	t_token	*token;
	int		j;

	j = 0;
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = malloc(sizeof(char) * alloc_str(line, i));
	if (!token->str)
		return (NULL);
	next_tokens2(line, i, &j, token);
	token->str[j] = '\0';
	return (token);
}

void	type_arg(t_token *token, int separator)
{
	if (ft_strcmp(token->str, "") == 0)
		token->type = EMPTY;
	else if (ft_strcmp(token->str, ">") == 0 && separator == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->str, ">>") == 0 && separator == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->str, "<") == 0 && separator == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->str, "|") == 0 && separator == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->str, ";") == 0 && separator == 0)
		token->type = END;
	else if (token->prev && token->prev->type >= TRUNC
		&& token->prev->type <= INPUT)
		token->type = ARG;
	else if (token->prev == NULL || token->prev->type >= TRUNC)
		token->type = CMD;
	else
		token->type = ARG;
}
