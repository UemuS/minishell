/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan <yihssan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:24:35 by yihssan           #+#    #+#             */
/*   Updated: 2021/06/16 17:24:36 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_inorout(t_cmd *ret, int inorout, char *file, int type)
{
	if (inorout == 1)
	{
		free(ret->output);
		ret->output = ft_strdup(file);
		ret->toappend = type == APPEND;
	}
	else
	{
		free(ret->input);
		ret->input = ft_strdup(file);
	}
}

int	bad_file(int fd, int *file, t_cmd *ret, char *str)
{
	*file = -1;
	free(ret->input);
	free(ret->output);
	ret->input = ft_strdup("");
	ret->output = ft_strdup("");
	write(2, "minishell :", 12);
	write(2, str, ft_strlen(str));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	close(fd);
	return (1);
}

int	ft_treat_fd(t_token *start, int file, t_cmd *ret)
{
	int		fd;
	int		inorout;
	int		otrapp;

	otrapp = O_APPEND;
	if (start->type == 3)
		otrapp = O_TRUNC;
	fd = 0;
	if (start->type == 3 || start->type == 4)
	{
		inorout = 1;
		fd = open(start->next->str, O_WRONLY | O_CREAT | otrapp, 0644);
	}
	else if (start->type == 5)
	{
		inorout = 2;
		fd = open(start->next->str, O_RDONLY);
	}
	if (fd == -1)
		file = bad_file(fd, &file, ret, start->next->str);
	else
		fill_inorout(ret, inorout, start->next->str, start->type);
	return (file);
}

int	ft_count_args(t_token *start)
{
	int	j;

	j = 0;
	while (start && (start->type <= 2 || start->type == 8))
	{
		start = start->next;
		j++;
	}
	return (j + 1);
}

int	ft_underscore(t_minishell *mysh, t_d_list *last)
{
	int	i;

	i = 0;
	while (ft_cmd(last->content)->args && ft_cmd(last->content)->args[i])
		i++;
	if (i > 0 && (ft_cmd(last->content)->args[i - 1])[0] != '\0')
		ft_fillenv(mysh, "_", ft_cmd(last->content)->args[i - 1]);
	else
		ft_fillenv(mysh, "_", ft_cmd(last->content)->str);
	return (i);
}
