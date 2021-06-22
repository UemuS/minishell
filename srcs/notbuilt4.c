/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notbuilt4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan <yihssan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 20:57:24 by yihssan           #+#    #+#             */
/*   Updated: 2021/06/16 16:58:25 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	notbuilt_err(char *s1)
{
	int	fd;

	fd = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("minishell ");
	if (s1)
		printf(": %s", s1);
	printf("\n");
	dup2(STDOUT_FILENO, fd);
	close(fd);
	return (1);
}

int	freeenv(t_d_list *env)
{
	free(ft_env(env->content)->alias);
	free(ft_env(env->content)->value);
	free(env->content);
	free(env);
	return (0);
}

int	ft_dounset(t_minishell *mysh, t_cmd *cmd, int rem)
{
	int			i;
	t_d_list	*head;

	i = 0;
	head = mysh->env;
	while (cmd->args && cmd->args[++i])
	{
		while (mysh->env && mysh->env->next
			&& ft_strcmp(ft_env(mysh->env->content)->alias, cmd->args[i]))
			mysh->env = mysh->env->next;
		if (ft_syntax(cmd->args[i])
			&& !ft_strcmp(ft_env(mysh->env->content)->alias, cmd->args[i]))
		{
			if (mysh->env->prev)
				mysh->env->prev->next = mysh->env->next;
			if (mysh->env->next)
				mysh->env->next->prev = mysh->env->prev;
			freeenv(mysh->env);
		}
		else if (!ft_syntax2(cmd->args[i]))
			rem = notbuilt_err("not a valid identifier");
		mysh->env = head;
	}
	return (rem);
}

int	ft_unsetalias(t_minishell *mysh, char *cmd)
{
	t_d_list	*head;
	int			rem;

	rem = 0;
	head = mysh->env;
	while (mysh->env && ft_strcmp(ft_env(mysh->env->content)->alias, cmd))
	{
		if (mysh->env->next)
			mysh->env = mysh->env->next;
		else
			break ;
	}
	if (!ft_strcmp(ft_env(mysh->env->content)->alias, cmd))
	{
		if (mysh->env->prev)
			mysh->env->prev->next = mysh->env->next;
		if (mysh->env->next)
			mysh->env->next->prev = mysh->env->prev;
		freeenv(mysh->env);
	}
	mysh->env = head;
	return (rem);
}
