/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 17:57:56 by laafilal          #+#    #+#             */
/*   Updated: 2021/06/14 14:51:17 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_str_isdigit(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	free_hisb(void *content)
{
	t_hisb	*hisb;

	hisb = content;
	free(hisb->line);
	free(hisb->backup);
	free(hisb);
}

void	print_on_terminal(t_minishell *mysh, char *ch)
{
	char	*tmp;

	if (!((t_hisb *)mysh->term.htmp->content)->backup)
	{
		free(((t_hisb *)mysh->term.htmp->content)->backup);
		((t_hisb *)mysh->term.htmp->content)->backup
			= ft_strdup(((t_hisb *)mysh->term.htmp->content)->line);
	}
	tmp = ft_strjoin(((t_hisb *)mysh->term.htmp->content)->line, ch);
	free(((t_hisb *)mysh->term.htmp->content)->line);
	((t_hisb *)mysh->term.htmp->content)->line = ft_strdup(tmp);
	free(tmp);
	if (isatty(STDIN))
		write(1, ch, 1);
}

int	ft_size(char **str)
{
	int			cnt;

	cnt = 0;
	while (str && str[cnt])
		cnt++;
	return (cnt);
}

int	ft_length(t_minishell mysh)
{
	t_d_list	*env;
	int			cnt;

	cnt = 0;
	env = mysh.env;
	while (env != NULL)
	{
		cnt++;
		env = env->next;
	}
	return (cnt);
}
