/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 13:23:58 by laafilal          #+#    #+#             */
/*   Updated: 2021/06/14 14:36:48 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_term(t_minishell *mysh)
{
	mysh->term.buffer = malloc(2048);
	mysh->term.terminal_type = ft_get_env("TERM", mysh->env);
	if (!mysh->term.terminal_type)
	{
		write(2, "getenv failed\n", 14);
		exit(1);
	}
	mysh->term.ret = tgetent(mysh->term.buffer, mysh->term.terminal_type);
	if (mysh->term.ret < 0 || mysh->term.ret == 0)
	{
		write(2, "Could not access the termcap data base , ", 41);
		write(2, "or Terminal type given is not defined\n", 38);
		exit(1);
	}
	mysh->term.line = ft_strdup("");
	if (!mysh->term.line)
		exit(1);
	mysh->term.htmp = NULL;
	ft_d_lstadd_front(&mysh->term.htmp,
		ft_d_lstnew(create_his(ft_strdup(""), NULL)));
	mysh->term.histories = mysh->term.htmp;
	g_sig_flag = SIG_NONE;
	mysh->term.echo_line = ft_strdup("");
	set_term_actions(mysh);
}

void	set_attr_term(struct termios *attr)
{
	int	at;

	at = tcsetattr(STDIN_FILENO, TCSANOW, attr);
	if (at == -1 && isatty(STDIN))
	{
		err_print(strerror(errno), NULL, NULL);
		exit (1);
	}
}

void	get_attr_term(struct termios *attr)
{
	int	at;

	at = tcgetattr(STDIN_FILENO, attr);
	if (at == -1 && isatty(STDIN))
	{
		err_print(strerror(errno), NULL, NULL);
		exit (1);
	}
}

void	term_config(t_minishell *mysh)
{
	get_attr_term(&(mysh->term.oldattr));
	mysh->term.newattr = mysh->term.oldattr;
	mysh->term.newattr.c_lflag &= ~ICANON;
	mysh->term.newattr.c_lflag &= ~ECHO;
	mysh->term.newattr.c_lflag &= ~ECHOE;
}

void	set_term_actions(t_minishell *mysh)
{
	mysh->term.action.clearstr = tgetstr("dl", &mysh->term.buffer);
	mysh->term.action.gotto = tgoto(tgetstr("cr", &mysh->term.buffer), 0, 0);
	mysh->term.action.del_c = tgetstr("dc", &mysh->term.buffer);
	mysh->term.action.key_back = tgetstr("kb", &mysh->term.buffer);
}
