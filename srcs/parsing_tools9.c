/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools9.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan <yihssan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 13:15:24 by yihssan           #+#    #+#             */
/*   Updated: 2021/06/11 14:58:59 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lsttri(t_pars *pars, int cmd, t_token *tmp)
{
	t_token	*file;
	t_token	*cmdpos;

	file = pars->start;
	cmdpos = pars->start->next;
	if (!cmd)
	{
		cmdpos->type = 1;
		cmd = 1;
	}
	while (pars->start->next && (pars->start->next->type <= 2
			|| pars->start->next->type == 8))
		pars->start = pars->start->next;
	file->next = pars->start->next;
	if (pars->start->next)
		pars->start->next->prev = file;
	pars->start->next = tmp;
	cmdpos->prev = tmp->prev;
	if (tmp->prev)
		tmp->prev->next = cmdpos;
	tmp->prev = pars->start;
}

void	sortlst(t_pars *pars)
{
	int		cmd;
	t_token	*tmp;

	cmd = 0;
	while (pars->start && pars->start->next)
	{
		cmd = pars->start->type == 1;
		cmd = cmd * !(pars->start->type >= 6 && pars->start->type <= 7);
		if (pars->start->type >= 3 && pars->start->type <= 5)
		{
			tmp = pars->start;
			pars->start = pars->start->next;
			while (pars->start->next && pars->start->next->type >= 3
				&& pars->start->next->type <= 5)
			{
				pars->start = pars->start->next;
				pars->start = pars->start->next;
			}
			if (pars->start->next && pars->start->next->type <= 2)
				ft_lsttri(pars, cmd, tmp);
		}
		if (pars->start->next)
			pars->start = pars->start->next;
	}
}
