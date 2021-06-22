/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notbuilt2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan <yihssan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 20:05:25 by yihssan           #+#    #+#             */
/*   Updated: 2021/06/16 21:36:45 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	helpexport(t_minishell *mysh, t_cmd *cmd, int i, t_env *exp)
{
	int	j;

	j = ft_cutmiddle(cmd->args[i]);
	exp->alias = ft_substr(cmd->args[i], 0, j);
	exp->value = ft_substr(cmd->args[i], j + 1, ft_strlen(cmd->args[i]));
	ft_fillenv(mysh, exp->alias, exp->value);
	free(exp->alias);
	free(exp->value);
}

int	ft_syntax(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i != 0 && str[i] == '=')
			return (1);
		if (!ft_isalpha(str[i]) && i == 0 && str[i] != '_')
			return (0);
		else if (str[i] != '_' && !ft_isdigit(str[i]) && !ft_isalpha(str[i]))
			return (0);
		i++;
	}
	return (2);
}

int	ft_syntax2(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && i == 0 && str[i] != '_')
			return (0);
		else if (str[i] != '_' && !ft_isdigit(str[i]) && !ft_isalpha(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_doecho(t_cmd *cmd)
{
	int		i;
	char	*str;
	int		rem;

	rem = 0;
	i = 0;
	str = ft_strdup("");
	while (cmd->args && cmd->args[++i])
	{
		if ((i == 1 || rem == 1) && ft_isflag(cmd->args[i]))
			rem = 1;
		else
		{
			str = ft_strjoin3(str, cmd->args[i]);
			if (cmd->args[i + 1])
				str = ft_strjoin3(str, " ");
			rem = 0;
		}
	}
	if (!cmd->args || !cmd->args[1] || !ft_isflag(cmd->args[1]))
		str = ft_strjoin3(str, "\n");
	write(1, str, ft_strlen(str));
	free(str);
	return (0);
}

int	ft_export(t_minishell *mysh, t_cmd *cmd)
{
	int			i;
	t_env		*exp;
	t_d_list	*head;
	int			rem;

	rem = 0;
	i = 0;
	head = mysh->env;
	exp = malloc(sizeof(t_env));
	while (cmd->args && cmd->args[++i])
	{
		if (ft_syntax(cmd->args[i]) == 1)
			helpexport(mysh, cmd, i, exp);
		else if (!ft_syntax(cmd->args[i]))
			rem = notbuilt_err("not a valid identifier");
		mysh->env = head;
	}
	free(exp);
	return (rem);
}
