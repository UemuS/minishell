/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools10.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan <yihssan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 14:41:24 by yihssan           #+#    #+#             */
/*   Updated: 2021/06/11 15:22:11 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unexpectedtoken(char *str, t_pars *pars, t_minishell *mysh)
{
	char	*ret;

	ret = ft_strjoin("syntax error near unexpected token ", str);
	ft_putendl_fd(ret, STDERR);
	pars->ret = 258;
	ft_fillseenv(mysh, "?", "258");
	if (ret)
		free(ret);
	return (1);
}

int	checksyntaxe(t_token *start, t_pars *pars, t_minishell *mysh)
{
	while (start)
	{
		if (!start->prev && start->type >= 6)
			return (unexpectedtoken(start->str, pars, mysh));
		if (start->next && start->type >= 3 && start->next->type >= 3)
		{
			if (!(start->type >= 6) || !(start->type <= 7)
				|| !(start->next->type >= 3) || !(start->next->type <= 5))
				return (unexpectedtoken(start->next->str, pars, mysh));
		}
		else if (!start->next)
		{
			if (start->type >= 3 && start->type <= 6)
				return (unexpectedtoken("newline", pars, mysh));
			else
				break ;
		}
		start = start->next;
	}
	return (0);
}

t_cmd	*init_cmd(void)
{
	t_cmd	*ret;

	ret = malloc(sizeof(t_cmd));
	ret->str = ft_strdup("");
	ret->input = NULL;
	ret->output = NULL;
	ret->args = NULL;
	ret->toappend = 0;
	ret->ret = 0;
	ret->pipe = 0;
	return (ret);
}

int	echoflag(t_token *flag)
{
	char	*str;
	int		i;

	if (!ft_strcmp(flag->str, "echo") && flag->next && flag->next->type == 2)
	{
		str = flag->next->str;
		if (!ft_strncmp(str, "-n", 2))
		{
			i = 1;
			while (str[++i])
			{
				if (str[i] != 'n')
					return (0);
			}
			return (1);
		}
	}
	return (0);
}

void	removecmd(t_token *start)
{
	while (start)
	{
		if (echoflag(start))
			start->next->type = 8;
		else if (start->type >= 3 && start->type <= 5)
		{
			if (start->next && start->next->type <= 2)
				start->next->type = 10;
		}
		start = start->next;
	}
}
