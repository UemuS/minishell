/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan <yihssan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 18:37:32 by laafilal          #+#    #+#             */
/*   Updated: 2021/06/16 17:19:37 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	prompt(void)
{
	if (isatty(STDIN))
	{
		write(1, "minishell-$: ", 13);
	}
}

void	read_line(t_minishell *mysh)
{
	int		ch;

	init_term(mysh);
	term_config(mysh);
	prompt();
	signals();
	while (1)
	{
		set_attr_term(&mysh->term.newattr);
		ch = get_c();
		catch_signal(mysh);
		if (ch == '\004')
			reached_eof(mysh);
		else if (ch == 0x7f)
			delete_char(mysh);
		else if (ch == 27)
			escape_seq(mysh, ch);
		else if (ch == '\n')
			reached_eol(mysh);
		else if (ch >= 31)
			print_on_terminal(mysh, (char *)(&ch));
		else if (!isatty(STDIN) && reached_eol(mysh))
			break ;
		set_attr_term(&mysh->term.oldattr);
	}
}

int	main(int ac, char **av, char **env)
{
	t_minishell	mysh;
	struct stat	fileStat;

	(void)ac;
	(void)av;
	if (ac > 1)
		return (0);
	mysh.term.line = NULL;
	if (lstat(av[1], &fileStat) == 0 && (S_ISDIR(fileStat.st_mode)
			|| (fileStat.st_mode & S_IXUSR)))
		exit(0);
	if (fstat(STDIN, &fileStat) == 0 && S_ISDIR(fileStat.st_mode))
		exit(0);
	mysh.env = ft_fill_env(env);
	mysh.seenv = ft_fillscretenv();
	ft_shell_lvl(&mysh);
	ft_fillseenv(&mysh, "?", "0");
	ft_unsetalias(&mysh, "OLDPWD");
	read_line(&mysh);
	return (0);
}
