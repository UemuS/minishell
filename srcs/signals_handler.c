/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 17:04:02 by laafilal          #+#    #+#             */
/*   Updated: 2021/06/17 11:37:20 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	s_handler(int sig)
{
	if (sig == 2)
	{
		write(1, "\n", 1);
		prompt();
		g_sig_flag = 2;
	}
	else if (sig == 3)
	{
		g_sig_flag = 0;
	}
}

void	catch_signal(t_minishell *mysh)
{
	if (g_sig_flag == 2)
	{
		g_sig_flag = 0;
		free(mysh->term.line);
		mysh->term.line = ft_strdup("");
		free(((t_hisb *)mysh->term.htmp->content)->line);
		((t_hisb *)mysh->term.htmp->content)->line = ft_strdup("");
		backup_manager(mysh);
		mysh->term.htmp = mysh->term.histories;
		ft_fillseenv(mysh, "?", "1");
	}
}

void	signals(void)
{
	signal(SIGINT, s_handler);
	signal(SIGQUIT, s_handler);
}
