/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 14:39:39 by laafilal          #+#    #+#             */
/*   Updated: 2021/06/16 15:16:38 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_exec_var(t_exec *exec, t_minishell *mysh)
{
	exec->pid = 0;
	exec->in = 0;
	exec->paths = get_paths(mysh);
	exec->cmd_str = NULL;
	exec->err_cmd = NULL;
	exec->env = NULL;
}

void	mapping_fds(t_cmd *cmd, t_exec *exec)
{
	if ((dup2(exec->in, STDIN_FILENO)) == -1)
		exit(1);
	if ((dup2(exec->out, STDOUT_FILENO)) == -1)
		exit(1);
	if (cmd->pipe)
	{
		close(exec->pipefd[0]);
		close(exec->pipefd[1]);
	}
}

void	piping_fd(t_cmd *cmd, t_minishell *mysh, t_exec *exec)
{
	if (cmd->pipe)
	{
		if (pipe(exec->pipefd) == -1)
		{
			free_all(exec->paths);
			x_free(mysh);
			exit(1);
		}
		exec->out = (exec->pipefd)[1];
		ft_fillenv(mysh, "_", cmd->str);
	}
	else
		exec->out = 1;
}

int	set_returns(t_cmd *cmd, t_minishell *mysh, int status)
{
	char	*tmp;

	if (cmd->pid == -1)
	{
		err_print("fork", strerror(errno), NULL);
		ft_fillseenv(mysh, "?", "1");
		return (1);
	}
	else
	{
		tmp = ft_itoa(WEXITSTATUS(status));
		if (sig_interuption(&status, cmd, mysh))
		{
			free(tmp);
			return (1);
		}
		ft_fillseenv(mysh, "?", tmp);
		free(tmp);
	}
	return (0);
}

t_hisb	*create_his(char *line, char *backup)
{
	t_hisb	*hisb;

	hisb = malloc(sizeof(t_hisb));
	hisb->line = line;
	hisb->backup = backup;
	return (hisb);
}
