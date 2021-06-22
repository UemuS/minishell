/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 14:58:39 by laafilal          #+#    #+#             */
/*   Updated: 2021/06/16 15:15:18 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**get_paths(t_minishell *mysh)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	path = ft_get_env("PATH", mysh->env);
	if (path)
		paths = ft_split2(path, ':');
	else
		paths = ft_split2(".", ':');
	while (paths[i])
	{
		if (paths[i][0] == '\0')
		{
			free(paths[i]);
			paths[i] = ft_strdup(".");
		}
		i++;
	}
	return (paths);
}

void	ft_set_newpwd(t_minishell *mysh, char *oldpath)
{
	char	path[PATH_M];

	if (getcwd(path, sizeof(path)) == NULL)
	{
		err_print((char *)((t_cmd *)mysh->cmd->content)->args[0],
			strerror(errno), NULL);
	}
	ft_fillenv(mysh, "OLDPWD", oldpath);
	ft_fillenv(mysh, "PWD", path);
}

char	**to_env(t_minishell mysh)
{
	char		**env;
	int			size;
	t_d_list	*l_env;
	int			i;
	char		*tmp;

	i = 0;
	size = ft_length(mysh) + 1;
	env = malloc(sizeof(char *) * size);
	l_env = mysh.env;
	while (i < size - 1)
	{
		tmp = ft_strjoin(((t_env *)l_env->content)->alias, "=");
		env[i] = ft_strjoin(tmp, ((t_env *)l_env->content)->value);
		free(tmp);
		l_env = l_env->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}
