/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 19:35:52 by laafilal          #+#    #+#             */
/*   Updated: 2021/06/09 19:36:50 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	set_fd_input(t_cmd *cmd, int *in)
{
	int	fdin;

	fdin = open(cmd->input, O_RDONLY);
	if (fdin == -1)
	{
		err_print(strerror(errno), NULL, NULL);
		return (1);
	}
	*in = fdin;
	return (0);
}

int	set_fd_output(t_cmd *cmd, int *out)
{
	int	fdout;
	int	to_append;

	to_append = 0;
	if (cmd->toappend == 0)
		to_append = O_TRUNC;
	else if (cmd->toappend == 1)
		to_append = O_APPEND;
	fdout = open(cmd->output, O_WRONLY | to_append);
	if (fdout == -1)
	{
		err_print(strerror(errno), NULL, NULL);
		return (1);
	}
	*out = fdout;
	return (0);
}

int	files_manager(t_cmd *cmd, int *in, int *out)
{
	if (cmd->input && cmd->input[0] != '\0')
	{
		if (set_fd_input(cmd, in))
			return (1);
	}
	if (cmd->output && cmd->output[0] != '\0')
	{
		if (set_fd_output(cmd, out))
			return (1);
	}
	return (0);
}
