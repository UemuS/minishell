/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 20:00:13 by laafilal          #+#    #+#             */
/*   Updated: 2021/06/17 15:40:02 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	cd_arg_empty_null(t_cmd *cmd, t_minishell *mysh, int *env_r)
{
	char	*env_p;

	env_p = NULL;
	if (cmd->args[1] == NULL)
	{
		env_p = ft_get_env("HOME", mysh->env);
		*env_r = chdir(env_p);
		if (*env_r == -1)
		{
			err_print(cmd->args[0], "HOME not set", NULL);
			return (1);
		}
	}
	else if (!ft_strcmp(cmd->args[1], "\0"))
		ft_set_newpwd(mysh, ft_get_env("PWD", mysh->env));
	else if (!ft_strcmp(cmd->args[1], ".") || !ft_strcmp(cmd->args[1], "./"))
	{
		env_p = ft_get_env("PWD", mysh->env);
		*env_r = chdir(env_p);
	}
	else
		*env_r = chdir(cmd->args[1]);
	return (0);
}

int	ft_docd(t_minishell *mysh, t_cmd *cmd)
{
	int		env_r;

	env_r = 0;
	if (cd_arg_empty_null(cmd, mysh, &env_r))
		return (1);
	if (env_r == -1)
	{
		err_print(cmd->args[0], cmd->args[1], strerror(errno));
		return (1);
	}
	ft_set_newpwd(mysh, ft_get_env("PWD", mysh->env));
	return (0);
}

int	ft_dopwd(t_cmd *cmd)
{
	char	path[PATH_M];

	if (getcwd(path, sizeof(path)) == NULL)
	{
		err_print(cmd->args[0], strerror(errno), NULL);
		return (1);
	}
	else
		printf("%s\n", path);
	return (0);
}

void	exit_error(t_cmd *cmd, t_minishell *mysh, long *status)
{
	errno = 0;
	*status = ft_atol(cmd->args[1]);
	if (errno == 34 || errno == 22)
	{
		err_print(cmd->str, cmd->args[1], "numeric argument required");
		x_free(mysh), exit(255);
	}
}

int	ft_doexit(t_minishell *mysh)
{
	t_cmd	*cmd;
	int		i;
	long	status;

	cmd = ft_cmd(mysh->cmd->content);
	i = ft_size(cmd->args);
	if (i > 2)
	{
		if (cmd->args[1])
			exit_error(cmd, mysh, &status);
		err_print(cmd->args[0], "too many arguments", NULL);
		ft_fillseenv(mysh, "?", "1");
		return (0);
	}
	else if (cmd->args[1])
	{
		exit_error(cmd, mysh, &status);
		x_free(mysh), exit(status);
	}
	x_free(mysh), exit(0);
	return (0);
}
