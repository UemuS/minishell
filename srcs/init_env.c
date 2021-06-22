/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 17:33:45 by laafilal          #+#    #+#             */
/*   Updated: 2021/06/09 18:50:38 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_d_list	*fill_var(char *line)
{
	t_d_list	*curr;

	curr = malloc(sizeof(t_d_list));
	curr->content = next_env(line);
	return (curr);
}

char	**ft_createseev(char *envs)
{
	int		i;
	char	**ret;

	ret = malloc(sizeof(char **) * (ft_strlen(envs) + 1));
	i = 0;
	while (envs[i])
	{
		ret[i] = ft_substr(envs, i, 1);
		ret[i] = ft_strjoin3(ret[i], "=");
		i++;
	}
	ret[i] = 0;
	return (ret);
}

t_d_list	*ft_fill_env(char **env)
{
	t_d_list	*prev;
	t_d_list	*curr;
	int			i;

	i = 0;
	prev = NULL;
	curr = NULL;
	while (env && env[i])
	{
		curr = fill_var(env[i]);
		curr->prev = prev;
		if (prev)
			prev->next = curr;
		prev = curr;
		i++;
	}
	if (curr)
		curr->next = NULL;
	while (curr && curr->prev)
		curr = curr->prev;
	return (curr);
}

t_d_list	*ft_fillscretenv(void)
{
	t_d_list	*prev;
	t_d_list	*curr;
	char		**env;
	int			i;

	i = 0;
	env = ft_createseev("?0123456789");
	prev = NULL;
	curr = NULL;
	while (env && env[i])
	{
		curr = fill_var(env[i]);
		curr->prev = prev;
		if (prev)
			prev->next = curr;
		prev = curr;
		i++;
	}
	freesenv(env);
	if (curr)
		curr->next = NULL;
	while (curr && curr->prev)
		curr = curr->prev;
	return (curr);
}
