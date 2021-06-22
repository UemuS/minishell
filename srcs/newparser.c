/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan <yihssan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:24:13 by yihssan           #+#    #+#             */
/*   Updated: 2021/06/16 17:24:14 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_forquotes(t_pars *pars, char **line, t_minishell *mysh)
{
	if (quotes(*line, MAX_INT))
	{
		ft_putendl_fd("problem with quotes !", STDERR);
		ft_fillseenv(mysh, "?", "1");
		pars->ret = 2;
		pars->start = NULL;
		return (1);
	}
	return (0);
}

void	resetlst(t_pars *pars)
{
	while (pars->start && pars->start->prev)
		pars->start = pars->start->prev;
}

char	*alilhelp(t_minishell *mysh, char *myline)
{
	if (myline[ft_nextline(myline)] && ft_nextlineexist(myline))
		myline = ft_substr2(myline, ft_nextline(myline) + 1, ft_strlen(myline));
	else
		mysh->endline = 1;
	return (myline);
}

char	*parse1(t_minishell *mysh, char *myline, char *line3, t_token *head)
{
	char	*line4;

	line3 = ft_cutline(myline);
	myline = alilhelp(mysh, myline);
	line4 = space_line(line3, mysh);
	free(line3);
	if (line4 && line4[0] != 0)
	{
		fill_tok(&mysh->pars, line4);
		removecmd(mysh->pars.start);
		sortlst(&mysh->pars);
		resetlst(&mysh->pars);
		head = mysh->pars.start;
		mysh->cmd = fill_cmds(&mysh->pars, mysh);
		free_tokens(head);
		free(line4);
		if (((t_cmd *)mysh->cmd->content)->str[0] != '\0')
			execution(mysh);
		else
			ft_fillseenv(mysh, "?", "1");
		free_tokens2(mysh);
	}
	return (myline);
}

void	parse(t_minishell *mysh, char *line)
{
	t_token	*head;
	char	*line2;
	char	*line3;
	char	*myline;

	mysh->endline = 0;
	if (check_forquotes(&mysh->pars, &line, mysh))
		return ;
	line2 = space_line2(line, mysh);
	fill_tok(&mysh->pars, line2);
	head = mysh->pars.start;
	free(line2);
	if (checksyntaxe(mysh->pars.start, &mysh->pars, mysh))
		return ;
	free_tokens(head);
	myline = ft_strdup(line);
	line3 = NULL;
	while (mysh->endline == 0)
		myline = parse1(mysh, myline, line3, head);
	free(myline);
}
