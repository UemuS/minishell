/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 18:45:46 by laafilal          #+#    #+#             */
/*   Updated: 2021/06/15 15:59:32 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	err_shlvl(char *value)
{
	write(2, "minishell : warning: shell level (", 33);
	write(2, value, ft_strlen(value));
	write(2, ")too high, resetting to 1\n", 26);
}

int	set_shlvl(t_minishell *mysh, char *shlvl_c)
{
	int		shlvl;
	char	*tmp;

	errno = 0;
	shlvl = atoi(shlvl_c);
	if (errno == 34 || errno == 22)
		ft_fillenv(mysh, "SHLVL", "1");
	else if (shlvl == 999)
		ft_fillenv(mysh, "SHLVL", "");
	else if (shlvl < 0)
		ft_fillenv(mysh, "SHLVL", "0");
	else
	{
		tmp = ft_itoa(++shlvl);
		if (shlvl - 1 > 999)
		{
			ft_fillenv(mysh, "SHLVL", "0");
			err_shlvl(tmp);
			free(tmp);
			return (0);
		}
		ft_fillenv(mysh, "SHLVL", tmp);
		free(tmp);
	}
	return (1);
}

int	ft_shell_lvl(t_minishell *mysh)
{
	char	*shlvl_c;

	shlvl_c = ft_get_env("SHLVL", mysh->env);
	if (!shlvl_c)
		return (1);
	if (!set_shlvl(mysh, shlvl_c))
		return (0);
	return (1);
}
