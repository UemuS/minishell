/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <afilal.lamiaa@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 16:51:51 by laafilal          #+#    #+#             */
/*   Updated: 2019/11/12 00:47:16 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *tmpl;

	if (!lst || !*lst || !del)
		return ;
	while (*lst)
	{
		tmpl = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		(*lst) = tmpl;
	}
}
