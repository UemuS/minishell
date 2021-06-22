/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan <yihssan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 19:47:49 by laafilal          #+#    #+#             */
/*   Updated: 2021/06/16 15:55:51 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_check_builtins(t_minishell *mysh)
{
	t_cmd	*cmd;
	char	*str;
	char	**buildins;
	int		i;

	cmd = (t_cmd *)(mysh->cmd->content);
	str = cmd->str;
	buildins = (char *[7]){"echo", "pwd", "env", \
	"export", "cd", "unset", "exit"};
	i = 0;
	while (i < 7)
	{
		if (!ft_strcmp(str, buildins[i]))
			return (i);
		i++;
	}
	return (-1);
}

int	ft_builin_exec(t_minishell *mysh, int type, t_cmd *cmd)
{
	int	status;
	int	pipe;

	pipe = 0;
	if (type == B_ECHO)
		status = ft_doecho(cmd);
	if (type == B_CD)
		status = ft_docd(mysh, cmd);
	if (type == B_PWD)
		status = ft_dopwd(cmd);
	if (type == B_EXPORT)
		status = ft_export(mysh, cmd);
	if (type == B_UNSET)
		status = ft_dounset(mysh, cmd, 0);
	if (type == B_ENV)
		status = ft_doenv(mysh->env);
	if (type == B_EXIT)
	{
		if ((t_d_list *)mysh->cmd->prev)
			pipe = ((t_cmd *)((t_d_list *)mysh->cmd->prev)->content)->pipe;
		if (!pipe)
			printf("exit\n");
		status = ft_doexit(mysh);
	}
	return (status);
}
