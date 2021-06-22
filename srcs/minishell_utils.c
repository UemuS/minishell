/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 13:29:18 by laafilal          #+#    #+#             */
/*   Updated: 2021/06/07 18:05:08 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_put_c(int c)
{
	return (write(1, &c, 1));
}

char	get_c(void)
{
	int		t;
	char	c;

	t = read(0, &c, 1);
	if (t)
		return (c);
	return (-1);
}

void	delete_line_char(t_minishell *mysh)
{
	tputs(mysh->term.action.key_back, 1, ft_put_c);
	tputs(mysh->term.action.del_c, 1, ft_put_c);
}

void	clean_term_line(t_minishell *mysh)
{
	tputs(mysh->term.action.clearstr, 1, ft_put_c);
	tputs(mysh->term.action.gotto, 1, ft_put_c);
}

void	refresh_term_line(t_minishell *mysh)
{
	clean_term_line(mysh);
	if (ft_strlen(mysh->term.echo_line) > 0)
		write(1, mysh->term.echo_line, ft_strlen(mysh->term.echo_line));
	prompt();
	write(1, ((t_hisb *)mysh->term.htmp->content)->line,
		ft_strlen(((t_hisb *)mysh->term.htmp->content)->line));
}
