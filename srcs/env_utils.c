/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 17:37:02 by laafilal          #+#    #+#             */
/*   Updated: 2021/06/09 18:36:04 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*ft_env(void *content)
{
	return (content);
}

char	*ft_get_env(char *line, t_d_list *env)
{
	while (env)
	{
		if (!ft_strcmp(line, ft_env(env->content)->alias))
			return (ft_env(env->content)->value);
		if (env->next)
			env = env->next;
		else
			break ;
	}
	return (NULL);
}

int	ft_eqpos(char *line)
{
	int		i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

t_env	*next_env(char *line)
{
	t_env	*ret;
	int		eqpos;

	eqpos = ft_eqpos(line);
	ret = malloc(sizeof(t_env));
	ret->alias = ft_substr(line, 0, eqpos);
	ret->value = ft_substr(line, eqpos + 1, ft_strlen(line));
	return (ret);
}

void	freesenv(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		free(env[i++]);
	free(env);
}
