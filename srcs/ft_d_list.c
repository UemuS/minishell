/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_d_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 13:21:00 by laafilal          #+#    #+#             */
/*   Updated: 2021/06/07 18:07:00 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_d_list	*ft_d_lstnew(void *content)
{
	t_d_list	*list;

	list = malloc(sizeof(t_d_list));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	list->prev = NULL;
	return (list);
}

void	ft_d_lstadd_front(t_d_list **alst, t_d_list *new)
{
	t_d_list	*front;

	if (!new)
		return ;
	if (!alst || !*alst)
	{
		*alst = new;
		return ;
	}
	front = new;
	front->next = *alst;
	if (*alst)
		(*alst)->prev = front;
	*alst = front;
}

void	ft_d_lstiter(t_d_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

void	f(void *content)
{
	t_hisb	*hisb;

	hisb = content;
	printf("('%s' | '%s')\n", hisb->line, hisb->backup);
}
