/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan <yihssan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:24:33 by yihssan           #+#    #+#             */
/*   Updated: 2021/06/16 17:24:34 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_fill_args(t_pars *pars)
{
	char	**ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char **) * ft_count_args(pars->start));
	while (pars->start && (pars->start->type <= 2 || pars->start->type == 8))
	{
		if (pars->start->type == 0)
			ret[i++] = ft_strdup("");
		else
			ret[i++] = ft_strdup(pars->start->str);
		if (pars->start->next)
			pars->start = pars->start->next;
		else
			break ;
	}
	ret[i] = NULL;
	return (ret);
}

t_cmd	*next_cmd(t_pars *pars)
{
	t_cmd	*ret;

	ret = init_cmd();
	while (pars->start && pars->start->type != 6 && pars->start->type != 7)
	{
		if (pars->start->type == 1)
		{
			free(ret->str);
			ret->str = ft_strdup(pars->start->str);
		}
		if (pars->start->type <= 2 || pars->start->type == 8)
			ret->args = ft_fill_args(pars);
		if (ret->ret == 0 && pars->start->type >= 3 && pars->start->type <= 5)
		{
			ret->ret = ft_treat_fd(pars->start, ret->ret, ret);
			pars->start = pars->start->next;
		}
		if (!pars->start || (pars->start->type != 6 && pars->start->type != 7))
			pars->start = pars->start->next;
	}
	if (pars->start && pars->start->type == 6)
		ret->pipe = 1;
	if (pars->start && (pars->start->type == 6 || pars->start->type == 7))
		pars->start = pars->start->next;
	return (ret);
}

t_d_list	*fill_cmds2(t_pars *pars)
{
	t_d_list	*curr;

	curr = malloc(sizeof(t_d_list));
	curr->content = next_cmd(pars);
	return (curr);
}

t_d_list	*fill_cmds(t_pars *pars, t_minishell *mysh)
{
	t_d_list	*prev;
	t_d_list	*curr;

	prev = NULL;
	curr = NULL;
	while (pars->start)
	{
		curr = fill_cmds2(pars);
		curr->prev = prev;
		if (prev)
			prev->next = curr;
		prev = curr;
	}
	if (curr)
	{
		ft_underscore(mysh, curr);
		curr->next = NULL;
	}
	while (curr && curr->prev)
		curr = curr->prev;
	return (curr);
}
