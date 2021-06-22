/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan <yihssan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 00:22:35 by laafilal          #+#    #+#             */
/*   Updated: 2021/06/16 15:51:06 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	waiting_process(int j, t_minishell *mysh, int *status, char *cmd_str)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	while (i < j)
	{
		cmd = mysh->cmd->content;
		waitpid(cmd->pid, status, 0);
		signal(SIGINT, s_handler);
		signal(SIGQUIT, s_handler);
		if (set_returns(cmd, mysh, *status))
			break ;
		free(cmd_str);
		if (mysh->cmd->next)
			mysh->cmd = mysh->cmd->next;
		i++;
	}
}

void	check_cmd(t_exec *exec, t_minishell *mysh, t_cmd *cmd)
{
	int			p;

	execute_bin(exec, mysh, cmd);
	if (ft_strchr(cmd->str, '/'))
		execute_no_bin_path(cmd, mysh, exec);
	else if (exec->bin == -1)
	{
		if (!exec->paths)
		{
			err_print(cmd->str, "No such file or directory", NULL);
			free_all(exec->paths);
			free_all(exec->env);
			x_free(mysh);
			exit(127);
		}
		p = 0;
		while (exec->paths && exec->paths[p])
		{
			execute_no_bin(exec, cmd, mysh, p);
			p++;
		}
	}
}

int	built_in_nofork(int bin, t_cmd *cmd, t_minishell *mysh)
{
	int		st;
	char	*tmp;

	st = 0;
	if (bin > 2 && !cmd->pipe && !mysh->cmd->prev)
	{
		st = ft_builin_exec(mysh, bin, cmd);
		if (!st)
		{
			if (mysh->cmd->next)
				mysh->cmd = mysh->cmd->next;
			else
				return (1);
		}
		else
		{
			tmp = ft_itoa(st);
			ft_fillseenv(mysh, "?", tmp);
			free(tmp);
			return (1);
		}
	}
	return (0);
}

int	execute_cmd(t_minishell *mysh, t_cmd *cmd, t_exec *exec)
{
	echo_special_case(cmd, mysh);
	piping_fd(cmd, mysh, exec);
	if (files_manager(cmd, &exec->in, &exec->out))
		return (1);
	set_attr_term(&mysh->term.oldattr);
	if (cmd->ret != 1)
	{
		exec->bin = ft_check_builtins(mysh);
		if (built_in_nofork(exec->bin, cmd, mysh))
			return (1);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		exec->pid = fork();
		child_process(mysh, cmd, exec);
	}
	else if (!cmd->pipe)
	{
		ft_fillseenv(mysh, "?", "1");
		return (1);
	}
	parent_process(cmd, exec);
	return (0);
}

void	execution(t_minishell *mysh)
{
	t_cmd	*cmd;
	t_exec	exec;
	int		status;
	int		j;

	j = 0;
	init_exec_var(&exec, mysh);
	while (mysh->cmd)
	{
		exec.err_flag = 0;
		cmd = (t_cmd *)(mysh->cmd->content);
		if (execute_cmd(mysh, cmd, &exec))
			break ;
		j++;
		if (mysh->cmd->next)
			mysh->cmd = mysh->cmd->next;
		else
			break ;
	}
	get_back_tohead(mysh);
	waiting_process(j, mysh, &status, exec.cmd_str);
	free_all(exec.paths);
	get_back_tohead(mysh);
}
