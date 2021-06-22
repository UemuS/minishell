/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notbuilt3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan <yihssan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 20:40:15 by yihssan           #+#    #+#             */
/*   Updated: 2021/06/12 20:43:35 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_fillnewenv(char *alias, char *value)
{
	t_env	*ret;

	ret = malloc(sizeof(t_env));
	ret->alias = ft_strdup(alias);
	ret->value = ft_strdup(value);
	return (ret);
}

void	ft_newenv(t_minishell *mysh, char *alias, char *value)
{
	t_d_list	*curr;

	curr = malloc(sizeof(t_d_list));
	if (value == NULL)
		curr->content = ft_fillnewenv(alias, "");
	else
		curr->content = ft_fillnewenv(alias, value);
	while (mysh->env && mysh->env->next)
		mysh->env = mysh->env->next;
	curr->next = NULL;
	if (mysh->env)
	{
		mysh->env->next = curr;
		curr->prev = mysh->env;
	}
	else
		curr->prev = NULL;
	while (curr && curr->prev)
		curr = curr->prev;
}

int	ft_fillseenv(t_minishell *mysh, char *alias, char *value)
{
	while (mysh->seenv && ft_strcmp(ft_env(mysh->seenv->content)->alias, alias))
	{
		if (mysh->seenv->next)
			mysh->seenv = mysh->seenv->next;
		else
			break ;
	}
	if (!ft_strcmp(ft_env(mysh->seenv->content)->alias, alias))
	{
		free(ft_env(mysh->seenv->content)->value);
		ft_env(mysh->seenv->content)->value = ft_strdup(value);
	}
	else
		ft_newenv(mysh, alias, value);
	while (mysh->seenv && mysh->seenv->prev)
		mysh->seenv = mysh->seenv->prev;
	return (0);
}

int	ft_fillenv(t_minishell *mysh, char *alias, char *value)
{
	while (mysh->env && ft_strcmp(ft_env(mysh->env->content)->alias, alias))
	{
		if (mysh->env->next)
			mysh->env = mysh->env->next;
		else
			break ;
	}
	if (!ft_strcmp(ft_env(mysh->env->content)->alias, alias))
	{
		free(ft_env(mysh->env->content)->value);
		if (value == NULL)
			ft_env(mysh->env->content)->value = ft_strdup("");
		else
			ft_env(mysh->env->content)->value = ft_strdup(value);
	}
	else
		ft_newenv(mysh, alias, value);
	while (mysh->env && mysh->env->prev)
		mysh->env = mysh->env->prev;
	return (0);
}
