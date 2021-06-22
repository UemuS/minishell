/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 13:26:50 by laafilal          #+#    #+#             */
/*   Updated: 2021/06/17 16:28:26 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	backup_manager(t_minishell *mysh)
{
	if (mysh->term.htmp != mysh->term.histories)
	{
		free(((t_hisb *)mysh->term.histories->content)->line);
		((t_hisb *)mysh->term.histories->content)->line
			= ft_strdup(mysh->term.line);
		if (((t_hisb *)mysh->term.htmp->content)->backup)
		{
			free(((t_hisb *)mysh->term.htmp->content)->line);
			((t_hisb *)mysh->term.htmp->content)->line
				= ((t_hisb *)mysh->term.htmp->content)->backup;
			((t_hisb *)mysh->term.htmp->content)->backup = NULL;
		}
	}
	free(((t_hisb *)mysh->term.histories->content)->backup);
	((t_hisb *)mysh->term.histories->content)->backup = NULL;
}

int	reached_eol(t_minishell *mysh)
{
	free(mysh->term.echo_line);
	mysh->term.echo_line = ft_strdup("");
	free(mysh->term.line);
	mysh->term.line = ft_strdup(((t_hisb *)mysh->term.htmp->content)->line);
	if (isatty(STDIN))
		printf("\n");
	backup_manager(mysh);
	if (ft_strlen(mysh->term.line) != 0 && g_sig_flag == 0)
	{
		ft_d_lstadd_front(&mysh->term.histories,
			ft_d_lstnew(create_his(ft_strdup(""), NULL)));
		parse(mysh, mysh->term.line);
	}
	mysh->term.htmp = mysh->term.histories;
	if (g_sig_flag == 0)
		prompt();
	return (1);
}

void	escape_seq(t_minishell *mysh, char ch)
{
	ch = getchar();
	ch = getchar();
	if (ch == 'A')
	{
		if (mysh->term.htmp->next)
			mysh->term.htmp = mysh->term.htmp->next;
		refresh_term_line(mysh);
	}
	else if (ch == 'B')
	{
		if (mysh->term.htmp)
		{
			if (mysh->term.htmp->prev)
				mysh->term.htmp = mysh->term.htmp->prev;
			refresh_term_line(mysh);
		}
	}
}

void	reached_eof(t_minishell *mysh)
{
	int	ret;

	ret = 0;
	if (ft_strlen(((t_hisb *)mysh->term.htmp->content)->line) == 0)
	{
		write(1, "exit\n", 5);
		ret = ft_atoi(ft_get_env("?", mysh->seenv));
		ft_lstclear((void *)&(mysh->term.histories), free_hisb);
		free_env(mysh->env);
		free_env(mysh->seenv);
		free(mysh->term.echo_line);
		free(mysh->term.line);
		set_attr_term(&mysh->term.oldattr);
		exit(ret);
	}
}

void	delete_char(t_minishell *mysh)
{
	int		l;
	char	*tmp;

	l = ft_strlen(((t_hisb *)mysh->term.htmp->content)->line);
	if (ft_strlen(((t_hisb *)mysh->term.htmp->content)->line) != 0)
	{
		delete_line_char(mysh);
		tmp = ft_strdup(((t_hisb *)mysh->term.htmp->content)->line);
		if (!((t_hisb *)mysh->term.htmp->content)->backup)
		{
			free(((t_hisb *)mysh->term.htmp->content)->backup);
			((t_hisb *)mysh->term.htmp->content)->backup = ft_strdup(tmp);
		}
		tmp[l - 1] = '\0';
		free(((t_hisb *)mysh->term.htmp->content)->line);
		((t_hisb *)mysh->term.htmp->content)->line = ft_strdup(tmp);
		free(tmp);
	}
	refresh_term_line(mysh);
}
