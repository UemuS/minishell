/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 19:28:28 by laafilal          #+#    #+#             */
/*   Updated: 2021/06/14 14:49:50 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_histo(t_d_list *hist)
{
	t_d_list	*tmp;
	t_hisb		*hisb;

	while (hist)
	{
		hisb = hist->content;
		free(hisb->backup);
		free(hisb->line);
		free(hisb);
		tmp = hist;
		hist = hist->next;
		free(tmp);
	}
	free(hist);
}

void	env_clear(void *content)
{
	t_env	*env;

	env = content;
	free(env->alias);
	free(env->value);
	free(env);
}

void	free_env(t_d_list *env)
{
	t_d_list	*tmp;

	while (env)
	{
		env_clear(env->content);
		tmp = env;
		env = env->next;
		free(tmp);
	}
}

void	x_free(t_minishell *mysh)
{
	set_attr_term(&mysh->term.oldattr);
	free(mysh->term.action.clearstr);
	free(mysh->term.action.gotto);
	free_env(mysh->env);
	free_env(mysh->seenv);
	free(mysh->term.echo_line);
	free(mysh->term.line);
	free_tokens2(mysh);
	free_histo(mysh->term.histories);
}

void	free_all(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}
